'use strict';

const bindings = require('./bindings');

const { EventEmitter } = require('events');

/**
 * @fileOverview Utilzes a pixel buffer comparison engine written in c++ for fast calculations.
 * Can be used by creating a new instance with set values and accessing the convenience methods.
 * Can be used statically by directly accessing the public c++ methods.
 * Outputs a percent based on how many pixels are changed between 2 pixel buffers.
 * @requires events.EventEmitter
 * @version v0.0.5
 */
class PixelChange extends EventEmitter {
    /**
     * @constructor
     * @param {Object} options - Configuration options.
     * @param {Number} options.width - Width of image.
     * @param {Number} options.height - Height of image.
     * @param {Number} options.depth - 1 for gray, 3 for rgb, or 4 for rgba.
     * @param {Number} options.difference - Difference level threshold ranging from 1 to 255. Lower number is more sensitive.
     * @param {Number} options.percent - Percent of pixels that meet or exceed difference threshold.
     * @param {Function} [callback] - Function to be called when pixel change is detected.
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

            //depth is number of bytes per pixel, gray = 1, rgb = 3, rgba = 4
            switch (this._depth) {
                case 1 :
                    this._pixelChangeEngine = bindings.compareGrayPixels.bind(this, this._width, this._height, this._difference);
                    break;
                case 3 :
                    this._pixelChangeEngine = bindings.compareRgbPixels.bind(this, this._width, this._height, this._difference);
                    break;
                case 4 :
                    this._pixelChangeEngine = bindings.compareRgbaPixels.bind(this, this._width, this._height, this._difference);
                    break;
                default :
                    throw new Error('Invalid depth, value must be 1 for gray, 3 for rgb, or 4 for rgba');
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
     * @param {Buffer} buf0 - Buffer array of pixels.
     * @param {Buffer} buf1 - Buffer array of pixels.
     * @public
     */
    compare(buf0, buf1) {
        const percent = this._pixelChangeEngine(buf0, buf1);
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
     * @param {Buffer} buf1 - Buffer array of pixels.
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
     * @param {Number} width - Width of image.
     * @param {Number} height - Height of image.
     * @param {Number} diff - Difference between 2 pixels, 1 - 255.
     * @param {Buffer} buf0 - Buffer array of pixels.
     * @param {Buffer} buf1 - Buffer array of pixels.
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
     * @param {Number} width - Width of image.
     * @param {Number} height - Height of image.
     * @param {Number} diff - Difference between 2 pixels, 1 - 255.
     * @param {Buffer} buf0 - Buffer array of pixels.
     * @param {Buffer} buf1 - Buffer array of pixels.
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
     * @param {Number} width - Width of image.
     * @param {Number} height - Height of image.
     * @param {Number} diff - Difference between 2 pixels, 1 - 255.
     * @param {Buffer} buf0 - Buffer array of pixels.
     * @param {Buffer} buf1 - Buffer array of pixels.
     * @returns {Number} - Returns the percentage of pixels that are different.
     * @static
     * @public
     */
    static compareRgbaPixels (width, height, diff, buf0, buf1) {
        return bindings.compareRgbaPixels(width, height, diff, buf0, buf1);
    }

}

module.exports = PixelChange;