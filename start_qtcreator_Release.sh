#!/bin/bash

set -e

SyntheticSchmup_CONFIGURATION=Release

source config.sh

/usr/bin/qtcreator CMakeLists.txt &
