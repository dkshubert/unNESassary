#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$SCRIPT_DIR/..

cd $PROJECT_ROOT

./tools/via_docker.sh /home/containeruser/unNES/tools/native/release.sh
