#!/bin/bash

set -e

SyntheticSchmup_CONFIGURATION=Release

source 1.config.sh

cd $BUILD_DIR/$SyntheticSchmup_CONFIGURATION

cmake $SOURCE_DIR -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=$SyntheticSchmup_CONFIGURATION
cmake $SOURCE_DIR -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=$SyntheticSchmup_CONFIGURATION # Do it twice, otherwise nothing will be generated

make -j4
