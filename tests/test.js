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

console.log('\nAssert = Error: A configuration object was expected\n');

assert.throws(
    () => {
        engine = pixelChange();
    },
    /Error: A configuration object was expected/
);

console.log('\nAssert = Error: Width must be greater than 0\n');

assert.throws(
    () => {
        engine = pixelChange({});
    },
    /Error: Width must be greater than 0/
);

console.log('\nAssert = Error: Height must be greater than 0\n');

assert.throws(
    () => {
        engine = pixelChange({width:1});
    },
    /Error: Height must be greater than 0/
);

console.log('\nAssert = Error: Depth must be 1, 3, or 4\n');

assert.throws(
    () => {
        engine = pixelChange({width:1, height:1, depth: 5});
    },
    /Error: Depth must be 1, 3, or 4/
);

console.log('\nAssert = Minimum values required to NOT throw\n');

engine = pixelChange({width: width, height: height, depth: depth});

assert(typeof engine.compare === 'function' && engine.compare.name === 'compare');

assert(typeof engine.compareSync === 'function' && engine.compareSync.name === 'compareSync');

/*--------------------------------------------------------------------------------------------------------------------*/

// gray

console.log('\ngray\n');

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

console.log('\nrgb\n');

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

console.log('\nrgba\n');

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