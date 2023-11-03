#!/bin/bash

set -xe

CFLAGS="-Wall -Wextra -ggdb -lraylib"
LIBS="-L/usr/local/lib"

mkdir -p build
clang $CFLAGS -o build/player player.c $LIBS
