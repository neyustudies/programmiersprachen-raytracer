#!/usr/bin/env python

import re
from numpy import arange


def main():
    with open("anim.sdf", "r") as f:
        content = f.read()
    i = 0
    for x in arange(0, 360, 1.5):
        frame = content
        frame = re.sub("{{ANGLE_0}}", "%s" % x, frame)
        frame = re.sub("{{ANGLE_1}}", "%s" % (2 * x + (45 - 15)), frame)
        frame = re.sub("{{IDX}}", "%04d" % i, frame)
        i += 1
        with open("anim/frame_%04d.sdf" % i, "w+") as f:
            f.write(frame)


if __name__ == "__main__":
    main()
