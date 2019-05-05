'use strict';

const fs = require('fs');

const path =  require('path');

const assert = require('assert');

const pixelChange = require('../index');

/*--------------------------------------------------------------------------------------------------------------------*/

// basic test for factory constructor

assert(typeof pixelChange === 'function' && pixelChange.name === 'CreateObject');

let engine = pixelChange({width: 1, height: 1, depth: 1});

assert(typeof engine.compare === 'function' && engine.compare.name === 'compare');

assert(typeof engine.compareSync === 'function' && engine.compareSync.name === 'compareSync');

/*--------------------------------------------------------------------------------------------------------------------*/

// do all of the gray tests first



/*--------------------------------------------------------------------------------------------------------------------*/

let pixelsArray = [];

for (let i = 1; i < 15; ++i) {
    const pixelPath = path.resolve(__dirname, '../pams/gray', `gray-${i}.pixels`);
    pixelsArray.push(fs.readFileSync(pixelPath));
}

//console.debug(pixelsArray);

/*--------------------------------------------------------------------------------------------------------------------*/

pixelsArray = [];

for (let i = 1; i < 15; ++i) {
    const pixelPath = path.resolve(__dirname, '../pams/rgb', `rgb-${i}.pixels`);
    pixelsArray.push(fs.readFileSync(pixelPath));
}

//console.debug(pixelsArray);

/*--------------------------------------------------------------------------------------------------------------------*/

pixelsArray = [];

for (let i = 1; i < 15; ++i) {
    const pixelPath = path.resolve(__dirname, '../pams/rgba', `rgba-${i}.pixels`);
    pixelsArray.push(fs.readFileSync(pixelPath));
}

//console.debug(pixelsArray);


