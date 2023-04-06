# Download base image ubuntu 22.04
FROM ubuntu:22.04

# Disable Prompt During Packages Installation
ARG DEBIAN_FRONTEND=noninteractive

# Update Ubuntu Software repository
RUN apt update
RUN apt upgrade -y

# Install dependencies. The `opengl/system` conan requirement
# really requires everything up to the kitchen sink. It would
# be nice to trim this list down, if possible, but it appears
# this full list is required to satisfy conan.
RUN apt install -y \
cmake \
clang-format \
python3-pip \
pkg-config \
doxygen \
libgl-dev \
libgl1-mesa-dev \
libx11-dev \
libx11-xcb-dev \
libfontenc-dev \
libice-dev \
libsm-dev \
libxau-dev \
libxaw7-dev \
libxcomposite-dev \
libxcursor-dev \
libxdamage-dev \
libxext-dev \
libxfixes-dev \
libxi-dev \
libxinerama-dev \
libxkbfile-dev \
libxmu-dev \
libxmuu-dev \
libxpm-dev \
libxrandr-dev \
libxrender-dev \
libxres-dev \
libxss-dev \
libxt-dev \
libxtst-dev \
libxv-dev \
libxvmc-dev \
libxxf86vm-dev \
libxcb-render0-dev \
libxcb-render-util0-dev \
libxcb-xkb-dev \
libxcb-icccm4-dev \
libxcb-image0-dev \
libxcb-keysyms1-dev \
libxcb-randr0-dev \
libxcb-shape0-dev \
libxcb-sync-dev \
libxcb-xfixes0-dev \
libxcb-xinerama0-dev \
libxcb-dri3-dev \
uuid-dev \
libxcb-util-dev \
libxcb-util0-dev

RUN pip install conan

# Setup project directory
RUN addgroup --gid 1000 groupcontainer
RUN adduser --uid 1000 --gid 1000 --home /home/containeruser containeruser
 
USER containeruser
RUN mkdir -p /home/containeruser/unNES
RUN conan profile detect
