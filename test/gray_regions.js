'use strict';

console.time('=====> testing gray pixel changes with regions set');

const assert = require('assert');

const P2P = require('pipe2pam');

const PixelChange = require('../index');

const { spawn } = require('child_process');

const PP = require('polygon-points');

const pp1 = new PP([{x:0,y:0}, {x:480,y:0}, {x:480, y:1080}, {x:0,y:1080}]);

const pp2 = new PP([{x:480,y:0}, {x:960,y:0}, {x:960, y:1080}, {x:480, y:1080}]);

const pp3 = new PP([{x:960,y:0}, {x:1440,y:0}, {x:1440, y:1080}, {x:960,y:1080}]);

const pp4 = new PP([{x:1440,y:0}, {x:1920,y:0}, {x:1920, y:1080}, {x:1440,y:1080}]);

const pamCount = 25;

let buf0, buf1;

let pamCounter = 0;

const diff = 5;

const width = 1920;
const height = 1080;

const bitset1 = pp1.getBitset(width, height);
const bitset2 = pp2.getBitset(width, height);
const bitset3 = pp3.getBitset(width, height);
const bitset4 = pp4.getBitset(width, height);

const regions = [{name: "one", diff: diff, count: bitset1.count, bitset: bitset1.buffer}, {name: "two", diff: diff, count: bitset2.count, bitset: bitset2.buffer}, {name: "three", diff: diff, count: bitset3.count, bitset: bitset3.buffer}, {name: "four", diff: diff, count: bitset4.count, bitset: bitset4.buffer}];

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

    /*'-rtsp_transport',
    'tcp',
    '-i',
    'rtsp://192.168.1.22:554/user=admin_password=pass_channel=1_stream=1.sdp',*/

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
        console.time('cpp gray regions');
        const percent0 = PixelChange.compareGrayRegions(width, height, regions, buf0, buf1);
        console.timeEnd('cpp gray regions');
        console.log('percent', percent0);
    });

});

const ffmpeg = spawn('ffmpeg', params, {stdio: ['ignore', 'pipe', 'inherit']});

ffmpeg.on('error', (error) => {
    console.log(error);
});

ffmpeg.on('exit', (code, signal) => {
    assert(code === 0, `FFMPEG exited with code ${code} and signal ${signal}`);
    console.timeEnd('=====> testing gray pixel changes with regions set');
});

ffmpeg.stdout.pipe(p2p);