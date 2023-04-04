#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$SCRIPT_DIR/..
BUILD_DIR=$PROJECT_ROOT/build

cd $PROJECT_ROOT
find . -iname *.h -o -iname *.cpp | xargs clang-format -i

conan install . --output-folder=$BUILD_DIR # --build missing

cd $BUILD_DIR
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
-DCMAKE_BUILD_TYPE=Release \
-DCOMPILE_WARNING_AS_ERROR=True

cmake --build .
