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
      const pixelPath = path.resolve(__dirname, '../pams/gray', `gray-${i}.pixels`);
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
          resultArray.push(results[0].percent);
        }
      });
    }

    assert.deepStrictEqual(resultArray, [1, 4, 6, 7, 7, 7, 6, 6, 6, 7, 7, 7], `❌  gray compareSync`);

    console.log('✅  gray compareSync');

    resultArray = [];

    for (let i = 0, j = 1; j <= 13; ++i, ++j) {
      const results = await compare(pixelsArray[i], pixelsArray[j]);
      if (results.length) {
        resultArray.push(results[0].percent);
      }
    }

    assert.deepStrictEqual(resultArray, [1, 4, 6, 7, 7, 7, 6, 6, 6, 7, 7, 7], `❌  gray compareAsync`);

    console.log('✅  gray compareAsync');

    /* --------------------------------------------------------------------------------------------------------------------*/

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

    engine = pixelChange({ width: width, height: height, depth: depth });

    compare = promisify(engine.compare.bind(engine));

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

    assert.deepStrictEqual(resultArray, [1, 4, 6, 8, 7, 8, 6, 4, 7, 8, 7, 8], `❌  rgb compareSync`);

    console.log('✅  rgb compareSync');

    resultArray = [];

    for (let i = 0, j = 1; j <= 13; ++i, ++j) {
      const results = await compare(pixelsArray[i], pixelsArray[j]);
      if (results.length) {
        resultArray.push(results[0].percent);
      }
    }

    assert.deepStrictEqual(resultArray, [1, 4, 6, 8, 7, 8, 6, 4, 7, 8, 7, 8], `❌  rgb compareAsync`);

    console.log('✅  rgb compareAsync');

    /* --------------------------------------------------------------------------------------------------------------------*/

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

    engine = pixelChange({ width: width, height: height, depth: depth });

    compare = promisify(engine.compare.bind(engine));

    for (let i = 0, j = 1; j <= 13; ++i, ++j) {
      engine.compareSync(pixelsArray[i], pixelsArray[j], (error, results, pixels) => {
        if (error) {
          console.error('my er', error);
        }
        if (results.length) {
          resultArray.push(results[0].percent);
        }
      });
    }

    assert.deepStrictEqual(resultArray, [1, 4, 6, 8, 7, 8, 6, 4, 6, 8, 7, 8], `❌  rgba compareSync`);

    console.log('✅  rgba compareSync');

    resultArray = [];

    for (let i = 0, j = 1; j <= 13; ++i, ++j) {
      const results = await compare(pixelsArray[i], pixelsArray[j]);
      if (results.length) {
        resultArray.push(results[0].percent);
      }
    }

    assert.deepStrictEqual(resultArray, [1, 4, 6, 8, 7, 8, 6, 4, 6, 8, 7, 8], `❌  rgba compareAsync`);

    console.log('✅  rgba compareAsync');

    console.log('🎉 success');

    process.exit(0);
  } catch (e) {
    console.error(e);
  }
})();
