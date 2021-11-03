'use strict';

const nodeGypBuild = require('node-gyp-build');

module.exports = nodeGypBuild(__dirname);

module.exports.path = nodeGypBuild.path();