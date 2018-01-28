'use strict';

//testing milliseconds of large buffers using static method of PixelChange to get percent of changed pixels

console.time('=====> testing pixel changes with no region set');

const assert = require('assert');

const P2P = require('pipe2pam');

const PixelChange = require('../index');

const { spawn } = require('child_process');

const pamCount = 25;

let buf0, buf1;

let pamCounter = 0;

let pixelChangeCounter = 0;

const pixelChangeResults = [ 13, 13, 12, 12, 12, 12, 13, 13, 12, 15, 13, 13, 12, 12, 12, 12, 13, 13, 12, 13, 13, 13, 12, 12 ];

const params = [
    /* log info to console */
    '-loglevel',
    'quiet',
    //'-stats',
    
    /* use an artificial video input */
    '-re',
    '-f',
    'lavfi',
    '-i',
    'testsrc=size=1920x1080:rate=15',

    /* set output flags */
    '-an',
    '-c:v',
    'pam',
    '-pix_fmt',
    'rgb24',
    '-f',
    'image2pipe',
    '-vf',
    'fps=1,scale=1920:1080',
    '-frames',
    pamCount,
    'pipe:1'
];

const compareRgbBound = PixelChange.compareRgbPixels.bind(PixelChange, 1920, 1080, 1);

const p2p = new P2P();

p2p.once('pam', (pam)=> {
    pamCounter++;

    buf1 = pam.pixels;

    p2p.on('pam', (pam)=> {
        pamCounter++;
        buf0 = buf1;
        buf1 = pam.pixels;

        console.time('rgb compare');
        const percent0 = PixelChange.compareRgbPixels(1920, 1080, 1, buf0, buf1);
        console.timeEnd('rgb compare');

        console.time('rgb compare bound');
        const percent1 = compareRgbBound(buf0, buf1);
        console.timeEnd('rgb compare bound');

        console.log(percent0, percent1);

        assert(percent0 === percent1, 'percent0 and percent 1 must be equal');
        assert(percent0 === pixelChangeResults[pixelChangeCounter++], 'pixel change percent is not correct');
    });

});

const ffmpeg = spawn('ffmpeg', params, {stdio: ['ignore', 'pipe', 'inherit']});

ffmpeg.on('error', (error) => {
    console.log(error);
});

ffmpeg.on('exit', (code, signal) => {
    assert(code === 0, `FFMPEG exited with code ${code} and signal ${signal}`);
    assert(pixelChangeCounter === pamCount - 1, `did not get ${pamCount - 1} pixel changes`);
    console.timeEnd('=====> testing pixel changes with no region set');
});

ffmpeg.stdout.pipe(p2p);