#!/bin/bash

# set debug to "on" when debugging is needed
# otherwise set to "off" for release version
_DEBUG="off"

# create bin dir if it doesn't exist
if [[ -d bin/ ]]; then
    echo "Bin Dir Exists; Skipping"
else
    mkdir ./bin/
fi

# create build dir if it doesn't exist
if [[ -d build/ ]]; then
    echo "Build Dir Exists; Skipping"
else
    mkdir ./build/
fi

rm -rf ./build/*
cd ./build/

if [[ "$_DEBUG" == "on" ]]; then
    cmake -DCMAKE_BUILD_TYPE=DEBUG ..; make;
else
    cmake ..; make;
fi
