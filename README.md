SyntheticSchmup
===============
Classic arcade shooter project


**TODO: explain how to use "config.bat" and "config.sh".**

Programming on linux
--------------------
First you need to install dependencies :
sudo apt install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev

Then launch "make_superbuild.sh" to install the dependencies.

// Finally you can launch "start_qtcreator_Debug.sh" or "start_qtcreator_Release.sh".

Programming on Windows
---------------------
First you need to have installed Visual Studio and Visual C++ (start a new C++ project on Visual Studio, this will download the generator).
Then launch "make_superbuild.bat", this will open a Visual Studio solution. Build the solution, this make take a few minutes because it will download dependencies over internet, then close Visual Studio.

// Finally you can launch "start_visualstudio_Debug.bat" or "start_visualstudio_Release.bat".