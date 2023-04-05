#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$SCRIPT_DIR/..
BUILD_DIR=$PROJECT_ROOT/build

cd $PROJECT_ROOT
doxygen .doxygen-conf
