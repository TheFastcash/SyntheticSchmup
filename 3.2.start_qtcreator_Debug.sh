#!/bin/bash

set -e

SyntheticSchmup_CONFIGURATION=Debug

source 1.config.sh

/usr/bin/qtcreator CMakeLists.txt &
