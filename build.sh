#!/bin/bash

set -xe

CFLAGS="-Wall -Wextra -ggdb `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib`"

clang $CFLAGS -o player player.c $LIBS
