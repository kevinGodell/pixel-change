# pixel-change
###### [![Build Status](https://travis-ci.org/kevinGodell/pixel-change.svg?branch=master)](https://travis-ci.org/kevinGodell/pixel-change) [![Build status](https://ci.appveyor.com/api/projects/status/fp7iei6tfdc9fqqy/branch/master?svg=true)](https://ci.appveyor.com/project/kevinGodell/pixel-change/branch/master) [![GitHub issues](https://img.shields.io/github/issues/kevinGodell/pixel-change.svg)](https://github.com/kevinGodell/pixel-change/issues) [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/kevinGodell/pixel-change/master/LICENSE)

**EXPERIMENTAL. FIRST ATTEMPT AT USING N-API WHICH IS ONLY SUPPORTED ON NODE 8.5 AND UP**

Measure differences between 2 identically sized buffer arrays of gray, rgb, or rgba pixels. Backed by c++ libraries iterating pixel buffers, converting to grayscale, measuring differences, and reporting back the percent of pixels that have changed.
