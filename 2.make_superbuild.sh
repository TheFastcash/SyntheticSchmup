#!/bin/bash

set -e

SyntheticSchmup_CONFIGURATION=Superbuild

source 1.config.sh

cd $BUILD_DIR/$SyntheticSchmup_CONFIGURATION

cmake $SOURCE_DIR -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=$SyntheticSchmup_CONFIGURATION

cmake $SOURCE_DIR -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=$SyntheticSchmup_CONFIGURATION

make -j4
