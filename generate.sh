#!/bin/sh

inputFile="Sample.json"
if [ ! -z "$@" ];
then
	if [ ! -z "$1" ];
	then
		inputFile="$1"
	fi
fi

cd build
./familytree -i "$inputFile" -o "output.dot"

cat output.dot | dot -Tpng -o output.png

