#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$SCRIPT_DIR/..
BUILD_DIR=$PROJECT_ROOT/build

cd $PROJECT_ROOT
conan install . --output-folder=$BUILD_DIR # --build missing

cd $BUILD_DIR
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
