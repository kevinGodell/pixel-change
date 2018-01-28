# pixel-change
###### [![Build Status](https://travis-ci.org/kevinGodell/pixel-change.svg?branch=master)](https://travis-ci.org/kevinGodell/pixel-change) [![Build status](https://ci.appveyor.com/api/projects/status/fp7iei6tfdc9fqqy/branch/master?svg=true)](https://ci.appveyor.com/project/kevinGodell/pixel-change/branch/master) [![GitHub issues](https://img.shields.io/github/issues/kevinGodell/pixel-change.svg)](https://github.com/kevinGodell/pixel-change/issues) [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/kevinGodell/pixel-change/master/LICENSE)

**EXPERIMENTAL. FIRST ATTEMPT AT USING N-API WHICH IS ONLY SUPPORTED ON NODE 8.5 AND UP**

Measure differences between 2 identically sized buffer arrays of gray, rgb, or rgba pixels. Backed by c++ libraries iterating pixel buffers, converting to grayscale, measuring differences, and reporting back the percent of pixels that have changed.

## installation
```
npm install pixel-change
```
## usage

```

const PixelChange = require('pixel-change');

/* -- access static methods -- */

//will return a percent of how many gray pixels are changed between the 2 buffer pixel arrays
const percent = PixelChange.compareGrayPixels(width, height, difference, buffer1, buffer2);

//will return a percent of how many rgb pixels are changed between the 2 buffer pixel arrays
const percent = PixelChange.compareRgbPixels(width, height, difference, buffer1, buffer2);

//will return a percent of how many rgba pixels are changed between the 2 buffer pixel arrays
const percent = PixelChange.compareRgbaPixels(width, height, difference, buffer1, buffer2);

/* -- access instance methods -- */

//create a new instance to access convenience methods
const pc = new PixelChange({width: 1920, height: 1080, depth: 3, difference: 25, percent: 12});

//listen to change event when percent of different pixels is detected
pc.on('change', (percent)=>{
    //do something when change event is dispatched because of percent
});

//compare 2 buffers, will dispatch event if change is detected
pc.compare(buffer1, buffer2);

//alternate convenience method, keep feeding pixel buffer via push
//instance will cache previous buffer to compare with next one pushed
pc.push(buffer);

/* -- alternative to listening to "change" event

//pass callback to new instance
const pc = new PixelChange({width: 1920, height: 1080, depth: 3, difference: 25, percent: 12}, (err, percent)=>{
    if (err) {
        throw err;
    }
    //do something when callback is called with percent
});