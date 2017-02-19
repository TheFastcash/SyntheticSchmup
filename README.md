# SyntheticSchmup

Classic arcade shooter project


### Getting started

First, make a copy of "config_default.bat" (or "config_default.sh" for linux), and rename it (the copy) "config.bat" (or "config.sh" for linux).  
Now open that file, and set the first 3 variables with full paths.  
*SOURCE_DIR* is the path containing the main "CMakeLists.txt", the root of the project.  
*BUILD_DIR* is the path where the project itself will be built (the folders "Debug", "Release" and "Superbuild" will be created automatically inside)  
*EXTERNALS_DIR* is the path where all externals libraries will be built (e.g. SFML)  
__Don't put any space around the = sign__

Programming on linux
--------------------
First you need to install dependencies :
sudo apt install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev

Then launch "make_superbuild.sh" to install external libraries.

Finally you can either :
* launch "prepare_(Debug|Release).sh" which will generate a .cbp project in $BUILD_DIR/$BUILD_TYPE,
* or launch "start_qtcreator_(Debug|Release).sh" and follow the steps on QtCreator (better choose the folder $BUILD_DIR/$BUILD_TYPE, but that is your choice anyway).

Programming on Windows
---------------------
First you need to have installed Visual Studio and Visual C++ (start a new C++ project on Visual Studio, this will download the generator).  
Then launch "make_superbuild.bat", this will open a Visual Studio solution. Build the solution (this make take a few minutes because it will download dependencies over internet) then close Visual Studio.

Finally you can launch "prepare_(Debug|Release).bat" then "launch_visualstudio_(Debug|Release).bat".


# ***Important***
###  *Temporary fixed error :*
Due to [an error in GCC 5.x](http://en.sfml-dev.org/forums/index.php?topic=20394.0), the CMakeLists.txt in src/Graphics in the official release of has been modified such as you can see [here](https://web.archive.org/web/20160509014317/https://gitlab.peach-bun.com/pinion/SFML/commit/3383b4a472f0bd16a8161fb8760cd3e6333f1782.patch).  
So in our main CMakeLists.txt file, the link which get the SFML archive https://www.dropbox.com/s/z6to2so4t15mqtf/SFML-2.4.0-sources.zip has the correction.
