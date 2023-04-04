#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$SCRIPT_DIR/..

cd $PROJECT_ROOT
find . -iname *.h -o -iname *.cpp | xargs clang-format -i

