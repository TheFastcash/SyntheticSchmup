# The location of the main CMakeLists.txt (actually, this is the folder where this file is located)
export SOURCE_DIR=  # e.g. /home/my_name/SyntheticSchmup
# The build destination of the project
export BUILD_DIR=  # e.g. /home/my_name/SyntheticSchmup-build-linux
# The external libraries destination (headers and libs)
export EXTERNALS_DIR=  # e.g. /home/my_name/SyntheticSchmup-externals-linux


# =========================================================

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi
if [ ! -d "$BUILD_DIR/Superbuild" ]; then
    mkdir "$BUILD_DIR/Superbuild"
fi
if [ ! -d "$BUILD_DIR/Release" ]; then
    mkdir "$BUILD_DIR/Release"
fi
if [ ! -d "$BUILD_DIR/Debug" ]; then
    mkdir "$BUILD_DIR/Debug"
fi

if [ "$SyntheticSchmup_CONFIGURATION" = "Debug" ] || [ "$SyntheticSchmup_CONFIGURATION" = "Release" ]; then
    export SFML_ROOT=$EXTERNALS_DIR/sfml/$SyntheticSchmup_CONFIGURATION
    export PATH=$SFML_ROOT/bin:$PATH
fi

