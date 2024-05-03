#!/bin/bash
# @Author: Xia Yunkai
# @Date:   2023-12-26 20:56:25
# @Last Modified by:   Xia Yunkai
# @Last Modified time: 2024-03-27 19:03:39

rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TPYE=Debug
make 