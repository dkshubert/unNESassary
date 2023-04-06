#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$SCRIPT_DIR/../..

cd $PROJECT_ROOT

./tools/native/format.sh
./tools/native/generate_docs.sh
./tools/native/build.sh
