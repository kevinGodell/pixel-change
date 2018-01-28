# pixel-change

**EXPERIMENTAL. FIRST ATTEMPT AT USING N-API WHICH IS ONLY SUPPORTED ON NODE 8.5 AND UP**

Measure differences between 2 buffer arrays of gray, rgb, or rgba pixels. Backed by c++ libraries iterating pixel buffers, converting to grayscale, measuring differences, and reporting back the percent of pixels that have changed.
