# prebuild instructions

1. update and tag version `npm version [<newversion> | major | minor | patch | premajor | preminor | prepatch | prerelease | from-git]`
2. push tags to trigger builds for appveyor and circleci
3. wait for ci to automatically deploy artifacts to github releases
4. download artifacts from github releases `npm run download`
5. verify package contents `npm run pack`
6. publish `npm publish`