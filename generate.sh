#!/bin/sh

cd build
./familytree

cat output.dot | dot -Tpng -o output.png
