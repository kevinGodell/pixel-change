#!/bin/bash

mkdir artifacts

export VERSION=$(node -p "require('./package.json').version")

export ARCHIVE_NAME="artifacts/$VERSION-$(uname -s)-$(uname -m).tar"

echo "$ARCHIVE_NAME"

tar --create --verbose --file="$ARCHIVE_NAME" --directory "./prebuilds/" linux-arm

gh release upload "$VERSION" "$ARCHIVE_NAME"

rm -rf artifacts