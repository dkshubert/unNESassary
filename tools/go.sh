#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$SCRIPT_DIR/..

cd $PROJECT_ROOT
./tools/build.sh
./tools/run.sh
