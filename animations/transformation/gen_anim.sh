#!/usr/bin/env bash

echo "Preparing directory..."
rm -fr anim
mkdir anim

echo "Generating SDF Files..."
./gen_anim.py

echo "Rendering..."
find anim -name "*.sdf" | parallel ../../build/source/raytracer
# find anim -name "*.sdf" -exec ../../build/source/raytracer {} \;
mv *ppm anim
cd anim

echo "Converting..."
find . -name "*ppm" -exec convert {} {}.png \;

echo "Exporting..."
ffmpeg -r 30 -i 'frame_%04d.ppm.png' -r 30 anim.mp4
