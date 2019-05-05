'use strict';

const fs = require('fs');

const path =  require('path');

const assert = require('assert');

const pixelChange = require('../index');

let engine;

let width;

let height;

let depth;

let pixelsArray;

let resultArray;

/*--------------------------------------------------------------------------------------------------------------------*/

// basic test for factory constructor

assert(typeof pixelChange === 'function' && pixelChange.name === 'CreateObject');

width = 100;

height = 100;

depth = 1;

engine = pixelChange({width: width, height: height, depth: depth});

assert(typeof engine.compare === 'function' && engine.compare.name === 'compare');

assert(typeof engine.compareSync === 'function' && engine.compareSync.name === 'compareSync');

/*--------------------------------------------------------------------------------------------------------------------*/

// gray

pixelsArray = [];

resultArray = [];

for (let i = 1; i <= 14; ++i) {
    const pixelPath = path.resolve(__dirname, '../pams/gray', `gray-${i}.pixels`);
    pixelsArray.push(fs.readFileSync(pixelPath));
}

width = 640;

height = 360;

depth = 1;

engine = pixelChange({width: width, height: height, depth: depth});

for (let i = 0, j = 1; j <= 13; ++i, ++j) {
    engine.compareSync(pixelsArray[i], pixelsArray[j], (error, results, pixels) => {
        if (error) {
            console.error(error);
        }
        if (results.length) {
            resultArray.push(results[0].percent);
        }
    });
}

assert.deepStrictEqual(resultArray,[ 1, 4, 6, 7, 7, 7, 6, 6, 6, 7, 7, 7 ]);

/*--------------------------------------------------------------------------------------------------------------------*/

// rgb

pixelsArray = [];

resultArray = [];

for (let i = 1; i <= 14; ++i) {
    const pixelPath = path.resolve(__dirname, '../pams/rgb', `rgb-${i}.pixels`);
    pixelsArray.push(fs.readFileSync(pixelPath));
}

width = 640;

height = 360;

depth = 3;

engine = pixelChange({width: width, height: height, depth: depth});

for (let i = 0, j = 1; j <= 13; ++i, ++j) {
    engine.compareSync(pixelsArray[i], pixelsArray[j], (error, results, pixels) => {
        if (error) {
            console.error(error);
        }
        if (results.length) {
            resultArray.push(results[0].percent);
        }
    });
}

assert.deepStrictEqual(resultArray, [ 1, 4, 6, 8, 7, 8, 6, 4, 7, 8, 7, 8 ]);

/*--------------------------------------------------------------------------------------------------------------------*/

// rgba

pixelsArray = [];

resultArray = [];

for (let i = 1; i <= 14; ++i) {
    const pixelPath = path.resolve(__dirname, '../pams/rgba', `rgba-${i}.pixels`);
    pixelsArray.push(fs.readFileSync(pixelPath));
}

width = 640;

height = 360;

depth = 4;

engine = pixelChange({width: width, height: height, depth: depth});

for (let i = 0, j = 1; j <= 13; ++i, ++j) {
    engine.compareSync(pixelsArray[i], pixelsArray[j], (error, results, pixels) => {
        if (error) {
            console.error(error);
        }
        if (results.length) {
            resultArray.push(results[0].percent);
        }
    });
}

assert.deepStrictEqual(resultArray, [ 1, 4, 6, 8, 7, 8, 6, 4, 6, 8, 7, 8 ]);