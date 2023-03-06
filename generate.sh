#!/bin/sh

cd build
./familytree -i "Sample.json" -o "output.dot"

cat output.dot | dot -Tpng -o output.png

