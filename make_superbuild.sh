#!/bin/bash

set -e

SyntheticSchmup_CONFIGURATION=Superbuild

source config.sh

cd $BUILD_DIR/Superbuild

cmake $SOURCE_DIR -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Superbuild

cmake $SOURCE_DIR -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Superbuild

make -j4
