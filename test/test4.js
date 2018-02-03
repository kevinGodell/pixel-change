'use strict';

//passing callback that will receive the percent of changed pixels and using convenience method .push()

console.time('=====> testing pixel changes with no region set');

const assert = require('assert');

const P2P = require('pipe2pam');

const PixelChange = require('../index');

const { spawn } = require('child_process');

const pamCount = 10;

let pamCounter = 0;

let pixelChangeCounter = 0;

const pixelChangeResults = [14, 14, 13, 13, 13, 13, 14, 14, 13];

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
    'fps=1,scale=400:225',
    '-frames',
    pamCount,
    'pipe:1'
];

const p2p = new P2P();

p2p.once('pam', (pam)=> {
    pamCounter++;

    //grab some config settings from first pam and cache the pixels for next time
    const pc = new PixelChange({width: pam.width, height: pam.height, depth: pam.depth, diff: 1, percent: 1}, (err, data)=>{
        if(err) {
            throw err;
        }
        assert(data === pixelChangeResults[pixelChangeCounter++], 'pixel change percent is not correct');
    })
        .push(pam.pixels);

    p2p.on('pam', (pam)=> {
        pamCounter++;
        pc.push(pam.pixels);
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