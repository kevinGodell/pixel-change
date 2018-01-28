'use strict';

const bindings = require('./bindings');

const { EventEmitter } = require('events');

class PixelChange extends EventEmitter {
    /**
     *
     * @constructor
     * @param {Object} [options] - Configuration options (REQUIRED).
     * @param {Number} [options.width] - Width of image (REQUIRED).
     * @param {Number} [options.height] - Height of image (REQUIRED).
     * @param {Number} [options.depth] - 1 for gray, 3 for rgb, or 4 for rgba (REQUIRED).
     * @param {Number} [options.difference] - Difference level threshold, 1-255. Lower number is more sensitive (REQUIRED)
     * @param {Number} [options.percent] - Percent of pixels that meet or exceed difference threshold (REQUIRED)
     * @return {PixelChange}
     */
    constructor(options, callback) {
        super(options);
        if (callback && typeof callback === 'function' && callback.length === 2) {
            this._callback = callback;
        }
        if (options && options.width && options.height && options.depth && options.difference && options.percent) {

            this._width = parseInt(options.width);
            this._height = parseInt(options.height);
            this._depth = parseInt(options.depth);
            this._difference = parseInt(options.difference);
            this._percent = parseInt(options.percent);

            //depth is number of bytes per pixel, gray = 1, rgb = 3, rgba = 4
            switch (this._depth) {
                case 1 :
                    this._pixelChangeEngine = bindings.compareGrayPixels;
                    break;
                case 3 :
                    this._pixelChangeEngine = bindings.compareRgbPixels;
                    break;
                case 4 :
                    this._pixelChangeEngine = bindings.compareRgbaPixels;
                    break;
                default :
                    throw new Error('Invalid depth, value must be 1 for gray, 3 for rgb, or 4 for rgba');
            }

            if (this._width < 1) {
                throw new Error('Invalid width, value must be a positive integer');
            }

            if (this._height < 1) {
                throw new Error('Invalid height, value must be a positive integer');
            }

            if (this._difference < 1 || this._difference > 255) {
                throw new Error('Difference value must be between 1 and 255');
            }

            if (this._percent < 1 || this._percent > 100) {
                throw new Error('Percent value must be between 1 and 100');
            }

            //byte size of image will be width * height * depth
            this._size = this._width * this._height * this._depth;

        } else {
            throw new Error('Constructor must be called with width, height, depth, difference, and percent');
        }

    }

    /**
     * Get the percentage of different pixels between 2 pixel buffers.
     *
     * @param buf0 {Buffer} - Buffer array of pixels.
     * @param buf1 {Buffer} - Buffer array of pixels.
     * @public
     */
    compare(buf0, buf1) {
        const percent = this._pixelChangeEngine(this._width, this._height, this._difference, buf0, buf1);
        /*
        todo
        - will have to make this dispatch an object to accommodate regions of difference.
        - currently will dispatch an event with a single percent because we currently only support whole image
        */
        if (percent >= this._percent) {
            if (this.listenerCount('change') > 0) {
                this.emit('change', percent);
            }
            if (this._callback) {
                this._callback(null, percent);
            }
        }
        return this;
    }

    /**
     * Convenience method to have instance cache previous Buffer and keep feeding to this.compare()
     *
     * @param buf1 {Buffer} - Buffer array of pixels.
     * @public
     */
    push(buf1) {
        if (this._buf0 && buf1) {
            this.compare(this._buf0, buf1);
        }
        this._buf0 = buf1;
        return this;
    }

    /**
     * Get the percentage of different pixels between 2 grayscale pixel buffers.
     *
     * @param width {Number} - Width of image.
     * @param height {Number} - Height of image.
     * @param diff {Number}- Difference between 2 pixels, 1-255.
     * @param buf0 {Buffer} - Buffer array of pixels.
     * @param buf1 {Buffer} - Buffer array of pixels.
     * @returns {Number} - Returns the percentage of pixels that are different.
     * @static
     * @public
     */
    static compareGrayPixels (width, height, diff, buf0, buf1) {
        return bindings.compareGrayPixels(width, height, diff, buf0, buf1);
    }

    /**
     * Get the percentage of different pixels between 2 rgb pixel buffers.
     *
     * @param width {Number} - Width of image.
     * @param height {Number} - Height of image.
     * @param diff {Number}- Difference between 2 pixels, 1-255.
     * @param buf0 {Buffer} - Buffer array of pixels.
     * @param buf1 {Buffer} - Buffer array of pixels.
     * @returns {Number} - Returns the percentage of pixels that are different.
     * @static
     * @public
     */
    static compareRgbPixels (width, height, diff, buf0, buf1) {
        return bindings.compareRgbPixels(width, height, diff, buf0, buf1);
    }

    /**
     * Get the percentage of different pixels between 2 rgba pixel buffers.
     *
     * @param width {Number} - Width of image.
     * @param height {Number} - Height of image.
     * @param diff {Number}- Difference between 2 pixels, 1-255.
     * @param buf0 {Buffer} - Buffer array of pixels.
     * @param buf1 {Buffer} - Buffer array of pixels.
     * @returns {Number} - Returns the percentage of pixels that are different.
     * @static
     * @public
     */
    static compareRgbaPixels (width, height, diff, buf0, buf1) {
        return bindings.compareRgbaPixels(width, height, diff, buf0, buf1);
    }

}

module.exports = PixelChange;