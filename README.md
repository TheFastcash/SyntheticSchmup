# SyntheticSchmup
__A classic arcade shooter project__

_Note : Use a markdown reader to read this file._

### Getting started

First, make a copy of "config_default.bat" (or "config_default.sh" for linux), and rename it (the copy) "config.bat" (or "config.sh" for linux).  
Now open that file, and set the first 3 variables with full paths:
- __*SOURCE_DIR*__ is the path containing the main "CMakeLists.txt", the root of the project.  
- __*BUILD_DIR*__ is the path where the project itself will be built (the folders "Debug", "Release" and "Superbuild" will be created automatically inside)  
- __*EXTERNALS_DIR*__ is the path where all externals libraries will be built (e.g. SFML)  

__Don't put any space around the "=" sign !__

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
First you need to have installed Visual Studio 2017 community (Visual C++15 Win64).
The components to install are :
- .NET:
  - .NET Framework 4.6.1 SDK
  - .NET Framework 4.6.1 targeting pack
  - .NET Framework 4.6.2 SDK
  - .NET Framework 4.6.2 targeting pack
- Code tools :
  - Static analysis tools
  - Text Template Transformation
- Compilers, build tools, and runtimes :
  - C# and Visual Basic Roslyn Compilers
  - C++/CLI support
  - Clang/C2 (experimental)
  - MSBuild
  - VC++ 2015.3 v140 toolset (x86,x64)
  - VC++ 2017 v141 toolset (x86,x64)
  - Visual C++ tools for CMake
  - Windows Universal CRT SDK
- Debugging and testing
  - C++ profiling tools
  - Just-In-Time debugger
- Development activities :
  - Visual Studio C++ core features
- Games and Graphics
  - Graphics debugger and GPU profiler for DirectX
- SDKs, libraries, and frameworks
  - Graphics Tools Windows 8.1 SDK
  - Visual C++ ATL support
  - Windows 10 SDK (10.0.15063.0) for Desktop C++ x86 and x64
  - Windows 8.1 SDK

Then launch "make_superbuild.bat", this will open a Visual Studio solution. Build the solution (this make take a few minutes because it will download dependencies over internet) then close Visual Studio.

Finally you can launch "prepare_(Debug|Release).bat" then "start\_visualstudio_(Debug|Release).bat".


# ***Important***
###  *Temporary fixed error :*
Due to [an error in GCC 5.x](http://en.sfml-dev.org/forums/index.php?topic=20394.0), the CMakeLists.txt in src/Graphics in the official release of has been modified such as you can see [here](https://web.archive.org/web/20160509014317/https://gitlab.peach-bun.com/pinion/SFML/commit/3383b4a472f0bd16a8161fb8760cd3e6333f1782.patch).  
So in our main CMakeLists.txt file, the link which get the SFML archive https://www.dropbox.com/s/z6to2so4t15mqtf/SFML-2.4.0-sources.zip has the correction.
