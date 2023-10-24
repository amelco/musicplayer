#!/bin/bash

set -xe

CFLAGS="-Wall -Wextra -ggdb -lraylib"
LIBS="-L/usr/local/lib"

clang $CFLAGS -o player player.c $LIBS
