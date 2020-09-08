# Programmiersprachen: Raytracer

## dependencies
```
cmake
xorg-dev
libglu1-mesa-dev
freeglut3-dev
libxi-dev
libxrandr-dev
```

## building
```
mkdir build
cmake ..
make
```

## running

Executables will be in `build/source`.  Run the ray tracer from the
`build/source` directory with one of the provided scenes:

```sh
$ ./raytracer ../../source/tests/simple3.sdf
[Info][SDF] Parsed 25 lines.
Rendering scene to 'image.ppm'...
```

![example render](doc/simple3.png)
