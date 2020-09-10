#!/usr/bin/env bash

mkdir lens_anim
./gen_lens_anim.py
find lens_anim -name "*.sdf" | parallel ../../build/source/raytracer
mv *ppm lens_anim
cd lens_anim
find . -name "*ppm" -exec convert {} {}.png \;
ffmpeg -r 30 -i 'lens_frame_%04d.ppm.png' -r 30 anim.mp4
