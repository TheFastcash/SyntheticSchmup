#!/bin/bash

set -e

SyntheticSchmup_CONFIGURATION=Debug

source config.sh

/usr/bin/qtcreator CMakeLists.txt &
