#!/bin/bash

cmake -B build -S . -DCMAKE_BUILD_TYPE=Release && cmake --build build && build/mosaic-test