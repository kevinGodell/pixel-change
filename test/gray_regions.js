'use strict';

//testing milliseconds of large buffers using static method of PixelChange vs js function to get percent of changed pixels

console.time('=====> testing pixel changes with no region set');

const assert = require('assert');

const P2P = require('pipe2pam');

const PixelChange = require('../index');

const { spawn } = require('child_process');

const PP = require('polygon-points');

const pp1 = new PP([{x:0,y:0}, {x:320,y:0}, {x:320, y:240}, {x:0,y:240}]);

const pp2 = new PP([{x:320,y:0}, {x:640,y:0}, {x:640, y:240}, {x:320,y:240}]);

const pp3 = new PP([{x:0,y:240}, {x:320,y:240}, {x:320, y:480}, {x:0,y:480}]);

const pp4 = new PP([{x:320,y:240}, {x:640,y:240}, {x:640, y:480}, {x:320,y:480}]);

const pamCount = 25;

//const diff = 25;

let buf0, buf1;

let pamCounter = 0;

//let pixelChangeCounter = 0;

//const pixelChangeResults = [ 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 15, 12, 12, 12, 12 ];

const width = 1920;

const height = 1080;

const wxh = width * height;

//create bitsets of 1's and 0's to indicate if index of pixel is in region
//bitset must be equal in length to width * height of pixels
//precalculated so that we do not have to calculate each pixel as we iterate

const region1 = Buffer.alloc(wxh, 0);

const region2 = Buffer.alloc(wxh, 0);

const region3 = Buffer.alloc(wxh, 0);

const region4 = Buffer.alloc(wxh, 0);

for (let y = 0, i = 0; y < height; y++) {
    for (let x = 0; x < width; x++, i++) {
        if (pp1.containsPoint(x, y)) {
            region1[i] = true;
        }
    }
}

for (let y = 0, i = 0; y < height; y++) {
    for (let x = 0; x < width; x++, i++) {
        if (pp2.containsPoint(x, y)) {
            region2[i] = true;
        }
    }
}

for (let y = 0, i = 0; y < height; y++) {
    for (let x = 0; x < width; x++, i++) {
        if (pp3.containsPoint(x, y)) {
            region3[i] = true;
        }
    }
}

for (let y = 0, i = 0; y < height; y++) {
    for (let x = 0; x < width; x++, i++) {
        if (pp4.containsPoint(x, y)) {
            region4[i] = true;
        }
    }
}

const regions = [{name: "one", difference: 1, count: pp1.pointsLength, bitset: region1}, {name: "two", difference: 1, count: pp2.pointsLength, bitset: region2}, {name: "three", difference: 1, count: pp3.pointsLength, bitset: region3}, {name: "four", difference: 1, count: pp4.pointsLength, bitset: region4}];

const params = [
    /* log info to console */
    '-loglevel',
    'quiet',
    //'-stats',
    
    /* use an artificial video input */
    /*'-re',
    '-f',
    'lavfi',
    '-i',
    'testsrc=size=1920x1080:rate=15',*/
    '-rtsp_transport',
    'tcp',
    '-i',
    'rtsp://192.168.1.22:554/user=admin_password=pass_channel=1_stream=1.sdp',

    /* set output flags */
    '-an',
    '-c:v',
    'pam',
    '-pix_fmt',
    'gray',
    //'rgb24',
    //'rgba',
    '-f',
    'image2pipe',
    '-vf',
    `fps=2,scale=${width}:${height}`,
    '-frames',
    pamCount,
    'pipe:1'
];

const p2p = new P2P();

p2p.once('pam', (pam)=> {
    pamCounter++;

    buf1 = pam.pixels;

    p2p.on('pam', (pam)=> {
        pamCounter++;
        buf0 = buf1;
        buf1 = pam.pixels;

        console.time('cpp gray compare');
        //console.log(buf0);
        //console.log(buf1);
        const percent0 = PixelChange.compareGrayRegions(width, height, regions, buf0, buf1);
        console.timeEnd('cpp gray compare');
        //console.log(percent0);
        //console.time('js rgb compare');
        //const percent1 = PixelChange.jsCompareRgbPixels(width, height, diff, buf0, buf1);
        //console.timeEnd('js rgb compare');

        //console.log(percent0, percent1);

        //assert(percent0 === percent1, 'percent0 and percent 1 must be equal');
        //assert(percent0 === pixelChangeResults[pixelChangeCounter++], 'pixel change percent is not correct');
        console.log('percent', percent0);
    });

});

const ffmpeg = spawn('ffmpeg', params, {stdio: ['ignore', 'pipe', 'inherit']});

ffmpeg.on('error', (error) => {
    console.log(error);
});

ffmpeg.on('exit', (code, signal) => {
    assert(code === 0, `FFMPEG exited with code ${code} and signal ${signal}`);
    //assert(pixelChangeCounter === pamCount - 1, `did not get ${pamCount - 1} pixel changes`);
    console.timeEnd('=====> testing pixel changes with no region set');
});

ffmpeg.stdout.pipe(p2p);