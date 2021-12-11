# prebuild instructions

1. update and tag version `npm version minor`
2. push tags to trigger appveyor build for windows, ubuntu, macos
3. wait for appveyor to deploy artifacts to github releases
4. download artifacts from github releases `npm run download`
5. verify package contents `npm run pack`
6. publish `npm publish`