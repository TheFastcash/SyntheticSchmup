
# The location of the main CMakeLists.txt (actually, this is the folder where this file is located)
export SOURCE_DIR=
# The build destination of the project
export BUILD_DIR=
# The external libraries destination (headers and libs)
export EXTERNALS_DIR=

if [ "$SyntheticSchmup_CONFIGURATION" = "Superbuild" ]; then
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
# elif [ "$SyntheticSchmup_CONFIGURATION" = "Debug" ] || [ "$SyntheticSchmup_CONFIGURATION" = "Release" ]; then
    # export SFML_ROOT=$EXTERNALS_DIR/$SyntheticSchmup_CONFIGURATION/sfml
    # export PATH=$PATH:/home/jessy/Dropbox/GitHub/SyntheticSchmup-externals
fi