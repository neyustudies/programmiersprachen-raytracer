#!/usr/bin/env bash

# 1. clone https://github.com/neyustudies/programmiersprachen-raytracer
# 2. prepare a scene at `/tmp/scene.sdf`
# 3. prepare fix fa242f54 at `/tmp/color.hpp`
# 4. from your cloned repo, run this script
# 5. Create the final timelapse:
#    ffmpeg -r 5 -pattern_type glob -i '/tmp/rt_*.png' -c:v libx264 -pix_fmt yuv420p -r 5 /tmp/t.mp4
#    ffmpeg -i /tmp/t.mp4 -vf reverse ~/timelapse.mp4

I=0

render() {
    rm -fr build
    cp /tmp/color.hpp framework  # backport fix fa242f54
    mkdir build
    cd build
    cmake ..
    make -j4 raytracer
    source/raytracer /tmp/scene.sdf
    convert image.ppm /tmp/rt_`printf "%04d" $I`.png
    (( I += 1 ))
    cd ..
    git checkout .
    git checkout HEAD~ && render
}

render
