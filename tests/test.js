'use strict';

(async () => {
    try {
        const fs = require('fs');

        const path = require('path');

        const assert = require('assert');

        const pixelChange = require('../index');

        const { promisify } = require('util');

        let errMsg;

        let engine;

        let compare;

        let width;

        let height;

        let depth;

        let pixelsArray;

        let resultArray;

        /* --------------------------------------------------------------------------------------------------------------------*/

        // basic test for factory constructor

        assert(typeof pixelChange === 'function' && pixelChange.name === 'CreateObject', `❌  typeof pixelChange === 'function' && pixelChange.name === 'CreateObject'`);

        width = 100;

        height = 100;

        depth = 1;

        errMsg = 'A configuration object was expected';

        assert.throws(
            () => {
                engine = pixelChange();
            },
            {
                message: errMsg,
            },
            `❌  ${errMsg}`
        );

        console.log(`✅  Assert = Error: ${errMsg}`);

        errMsg = 'Width must be greater than 0';

        assert.throws(
            () => {
                engine = pixelChange({});
            },
            {
                message: errMsg,
            },
            `❌  ${errMsg}`
        );

        console.log(`✅  Assert = Error: ${errMsg}`);

        errMsg = 'Height must be greater than 0';

        assert.throws(
            () => {
                engine = pixelChange({ width: 1 });
            },
            {
                message: errMsg,
            },
            `❌  ${errMsg}`
        );

        console.log(`✅  Assert = Error: ${errMsg}`);

        errMsg = 'Depth must be 1, 3, or 4';

        assert.throws(
            () => {
                engine = pixelChange({ width: 1, height: 1, depth: 5 });
            },
            {
                message: errMsg,
            },
            `❌  ${errMsg}`
        );

        console.log(`✅  Assert = Error: ${errMsg}`);

        engine = pixelChange({ width: width, height: height, depth: depth });

        assert(typeof engine.compare === 'function' && engine.compare.name === 'compare', `❌  typeof engine.compare === 'function' && engine.compare.name === 'compare'`);

        assert(
            typeof engine.compareSync === 'function' && engine.compareSync.name === 'compareSync',
            `❌  typeof engine.compareSync === 'function' && engine.compareSync.name === 'compareSync'`
        );

        console.log('✅  Assert = Minimum values required to NOT throw');

        /* --------------------------------------------------------------------------------------------------------------------*/

        // gray

        pixelsArray = [];

        resultArray = [];

        for (let i = 1; i <= 14; ++i) {
            const pixelPath = path.resolve(__dirname, '../pixel-change-test/pixels/gray', `gray-${i}.pixels`);
            pixelsArray.push(fs.readFileSync(pixelPath));
        }

        width = 640;

        height = 360;

        depth = 1;

        engine = pixelChange({ width: width, height: height, depth: depth });

        compare = promisify(engine.compare.bind(engine));

        for (let i = 0, j = 1; j <= 13; ++i, ++j) {
            engine.compareSync(pixelsArray[i], pixelsArray[j], (error, results, pixels) => {
                if (error) {
                    console.error(error);
                }
                if (results.length) {
                    // console.log(results);
                    resultArray.push(Math.trunc((results[0].percent) * 100) / 100);
                }
            });
        }

        assert.deepStrictEqual(resultArray, [0.11, 1.85, 4.66, 6.51, 7.91, 7.28, 7.87, 6.47, 6.21, 6.61, 7.89, 7.24, 7.9], `❌  gray compareSync`);

        console.log('✅  gray compareSync');

        resultArray = [];

        for (let i = 0, j = 1; j <= 13; ++i, ++j) {
            const results = await compare(pixelsArray[i], pixelsArray[j]);
            if (results.length) {
                resultArray.push(Math.trunc((results[0].percent) * 100) / 100);
            }
        }

        assert.deepStrictEqual(resultArray, [0.11, 1.85, 4.66, 6.51, 7.91, 7.28, 7.87, 6.47, 6.21, 6.61, 7.89, 7.24, 7.9], `❌  gray compareAsync`);

        console.log('✅  gray compareAsync');

        /* --------------------------------------------------------------------------------------------------------------------*/

        // rgb

        pixelsArray = [];

        resultArray = [];

        for (let i = 1; i <= 14; ++i) {
            const pixelPath = path.resolve(__dirname, '../pixel-change-test/pixels/rgb', `rgb-${i}.pixels`);
            pixelsArray.push(fs.readFileSync(pixelPath));
        }

        width = 640;

        height = 360;

        depth = 3;

        engine = pixelChange({ width: width, height: height, depth: depth });

        compare = promisify(engine.compare.bind(engine));

        for (let i = 0, j = 1; j <= 13; ++i, ++j) {
            engine.compareSync(pixelsArray[i], pixelsArray[j], (error, results, pixels) => {
                if (error) {
                    console.error(error);
                }
                if (results.length) {
                    resultArray.push(Math.trunc((results[0].percent) * 100) / 100);
                }
            });
        }

        assert.deepStrictEqual(resultArray, [0.13, 1.96, 4.96, 6.98, 8.52, 7.84, 8.49, 6.89, 4.88, 7.04, 8.52, 7.80, 8.50], `❌  rgb compareSync`);

        console.log('✅  rgb compareSync');

        resultArray = [];

        for (let i = 0, j = 1; j <= 13; ++i, ++j) {
            const results = await compare(pixelsArray[i], pixelsArray[j]);
            if (results.length) {
                resultArray.push(Math.trunc((results[0].percent) * 100) / 100);
            }
        }

        assert.deepStrictEqual(resultArray, [0.13, 1.96, 4.96, 6.98, 8.52, 7.84, 8.49, 6.89, 4.88, 7.04, 8.52, 7.80, 8.50], `❌  rgb compareAsync`);

        console.log('✅  rgb compareAsync');

        /* --------------------------------------------------------------------------------------------------------------------*/

        // rgba

        pixelsArray = [];

        resultArray = [];

        for (let i = 1; i <= 14; ++i) {
            const pixelPath = path.resolve(__dirname, '../pixel-change-test/pixels/rgba', `rgba-${i}.pixels`);
            pixelsArray.push(fs.readFileSync(pixelPath));
        }

        width = 640;

        height = 360;

        depth = 4;

        engine = pixelChange({ width: width, height: height, depth: depth });

        compare = promisify(engine.compare.bind(engine));

        for (let i = 0, j = 1; j <= 13; ++i, ++j) {
            engine.compareSync(pixelsArray[i], pixelsArray[j], (error, results, pixels) => {
                if (error) {
                    console.error('my er', error);
                }
                if (results.length) {
                    resultArray.push(Math.trunc((results[0].percent) * 100) / 100);
                }
            });
        }

        assert.deepStrictEqual(resultArray, [0.12, 1.88, 4.8, 6.73, 8.19, 7.54, 8.17, 6.66, 4.71, 6.8, 8.2, 7.5, 8.19], `❌  rgba compareSync`);

        console.log('✅  rgba compareSync');

        resultArray = [];

        for (let i = 0, j = 1; j <= 13; ++i, ++j) {
            const results = await compare(pixelsArray[i], pixelsArray[j]);
            if (results.length) {
                //resultArray.push(results[0].percent);
                resultArray.push(Math.trunc((results[0].percent) * 100) / 100);
            }
        }

        assert.deepStrictEqual(resultArray, [0.12, 1.88, 4.8, 6.73, 8.19, 7.54, 8.17, 6.66, 4.71, 6.8, 8.2, 7.5, 8.19], `❌  rgba compareAsync`);

        console.log('✅  rgba compareAsync');

        console.log('🎉 success');

        process.exit(0);
    } catch (e) {
        console.error(e);
    }
})();