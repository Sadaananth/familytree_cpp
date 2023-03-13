#!/bin/sh

inputFile="Sample.json"
if [ ! -z "$@" ];
then
	if [ ! -z "$1" ];
	then
		inputFile="$1"
	fi
fi

inputFilePath=$(readlink -f $inputFile)

cd build/src/
./familytreegen -i "$inputFilePath" -o "output.dot"

cat output.dot | dot -Tpng -o output.png

