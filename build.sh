#!/bin/sh

buildType="RELEASE"

if [ ! -z "$@" ];
then
	if [ "$1" = "g" ];
	then
		buildType="DEBUG"
	fi
fi
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE="$buildType" && make -j5
