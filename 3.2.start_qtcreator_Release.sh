#!/bin/bash

set -e

SyntheticSchmup_CONFIGURATION=Release

source 1.config.sh

/usr/bin/qtcreator CMakeLists.txt &
