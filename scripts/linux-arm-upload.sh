#!/bin/bash

mkdir artifacts

VERSION="v$(node -p "require('./package.json').version")"

ARCHIVE_NAME="artifacts/$VERSION-$(uname -s)-$(uname -m).tar"

tar --create --verbose --file="$ARCHIVE_NAME" --directory "./prebuilds/" linux-arm

gh release upload "$VERSION" "$ARCHIVE_NAME"

rm -rf artifacts