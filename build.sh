#!/bin/bash
if [ ! -d "build" ]; then # 修正済み
    mkdir build
fi

cd build
cmake ..
make
