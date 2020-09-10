#!/usr/bin/env python

import re
from numpy import arange


def main():
    with open("lens.sdf", "r") as f:
        content = f.read()
    i = 0
    for x in arange(-30, 30, 0.2):
        frame = re.sub("{{LENS_X}}", "%s" % x, content)
        frame = re.sub("{{IDX}}", "%04d" % i, frame)
        i += 1
        with open("lens_anim/frame_%04d.sdf" % i, "w+") as f:
            f.write(frame)


if __name__ == "__main__":
    main()
