#!/bin/bash -eux

SCRIPT_DIR=$(dirname $0)
PROJECT_ROOT=$(realpath $SCRIPT_DIR/..)
BUILD_DIR=$PROJECT_ROOT/build
DOCKER_IMAGE=unnes/build-image

cd $PROJECT_ROOT
docker build -t $DOCKER_IMAGE .
docker run \
-v $PROJECT_ROOT:/home/containeruser/unNES \
-it $DOCKER_IMAGE $@
