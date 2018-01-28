# pixel-change
###### [![Build Status](https://travis-ci.org/kevinGodell/pixel-change.svg?branch=master)](https://travis-ci.org/kevinGodell/pixel-change) [![Build status](https://ci.appveyor.com/api/projects/status/fp7iei6tfdc9fqqy/branch/master?svg=true)](https://ci.appveyor.com/project/kevinGodell/pixel-change/branch/master) [![GitHub issues](https://img.shields.io/github/issues/kevinGodell/pixel-change.svg)](https://github.com/kevinGodell/pixel-change/issues) [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/kevinGodell/pixel-change/master/LICENSE)
Parser that works with ffmpeg to read piped data and fragment mp4 into an initialization segment and media segments. It can also get the codec info and generate an fmp4 HLS m3u8 playlist. ***Must use the following flags with ffmpeg targeting the output***: *-f mp4 -movflags +faststart+frag_keyframe*.


**EXPERIMENTAL. FIRST ATTEMPT AT USING N-API WHICH IS ONLY SUPPORTED ON NODE 8.5 AND UP**

Measure differences between 2 buffer arrays of gray, rgb, or rgba pixels. Backed by c++ libraries iterating pixel buffers, converting to grayscale, measuring differences, and reporting back the percent of pixels that have changed.
