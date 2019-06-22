# BearFite

BearFite is a single-player computer game centered around fighting bears. The original game was written in [TI-BASIC](https://en.wikipedia.org/wiki/TI-BASIC) by [ConsiderablyLargeCat](https://github.com/ConsiderablyLargeCat) during a particularly boring statistics class which required all students to have a graphing calculator. Development of the calculator version ended once the program filled up all available space on the TI-84, and the computer version was born.

## Playing The Game

BearFite is still in the early stages of development. Once there's been a stable release of the game, you'll find instructions here for how to download and play it.

## Building The Game

If you want build and run the game on your machine, follow the instructions below.

### Linux

Ooh, cool! You run Linux? You must know all the computer stuff. I'm sure you don't need help figuring this out.

### Mac

... Huh?

#### You Known, Macintosh?

Like the fruit?

#### No

Oh, okay

### Windows

You're going to need a C++ compiler and SFML.

#### C++ Compiler

We recommend [MinGW](http://www.mingw.org/). Instructions for installing MinGW can be found [here](http://www.mingw.org/wiki/Getting_Started). We recommend using cmd.exe to run g++. If you choose to go this route you'll want to change your path, as the instructions correctly note. Unfortunately, the instructions for *how* to change your path are out of date since the release of Windows 10. Try following the instructions [here](https://www.howtogeek.com/118594/how-to-edit-your-system-path-for-easy-command-line-access/) instead. At this point, you should be able to compile a file (e.g. HelloWorld.cpp) by changing your current directory to the folder that the file lives in, and running the command `g++ HelloWorld.cpp`. (Please *do* check that this works before you go any further.)

#### SFML

You'll also need [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library). You'll want the 32-bit MinGW version if you're using MinGW as we recommended above. As of this writing, the latest version is available [here](https://www.sfml-dev.org/download/sfml/2.4.2/). Since there's not a tutorial on the SFML webpage for setting up SFML when you're not using an IDE, we've included some instructions (but see the disclaimer at the end of this section):

Inside of the folder you just downloaded, there are three folders which are important for us right now: bin, lib, and include.

* The bin folder contains DLLs. We're going to be dynamically linking our applications to SFML. To run any executables built using SFML, you'll need to copy all of the relevant DLLs into the same folder as the application. (Which are the relevant ones? The easy solution is to just copy all of them. If you are bothered by the easy solution: As of this writing BearFite doesn't contain audio, so openall.dll, sfml-graphics-2.dll, sfml-window-2.dll, and sfml-system-2.dll should suffice to run BearFite.)

* The lib folder contains libraries (files with the .a extension). If you go to the folder where you installed MinGW (the default is C:\MinGW), and then follow the path \lib\gcc\mingw32\6.3.0 (replace 6.3.0 by whatever version you have), you should be in a folder with a few subfolders, some .o files, and a bunch of .a files. Copy into here all of the files from the SFML lib folder. Now MinGW knows about the SFML libraries.

* Lastly, the include folder contains a folder named SFML, which contains all of the SFML header files. Copy the folder named SFML from inside of the include folder. Now remember the folder that we dumped all of the .a files into in the last step? That folder should have a subfolder named include, which contains a folder named C++, which contains all of the standard C++ headers (iostream, algorithm, etc.). Into that C++ folder paste the SFML folder that we picked up just a second ago. (Not the *contents* of the folder, but rather the folder itself.) Now MinGW knows about the SFML headers, so we can #include them as needed.

You should now compile and run a test program which uses SFML to make sure things work. The sample program at that end of [this tutorial](https://www.sfml-dev.org/tutorials/2.4/start-cb.php) is a good choice for this step.

**Disclaimer:** Copying the libraries and include folder is not the method recommended by SFML. Instead, they suggest using command line arguments to tell the compiler where to look. We use the method above for BearFite because it's what we stumbled upon via trial and error when first trying to get SFML to work.

#### Building BearFite

If you have MinGW and SFML working on your computer, building the game is straightforward:

* Download this project from GitHub to some folder on your computer

* Open cmd.exe, and change the current directory to the folder you put BearFite in.

* Run Make.cmd

Don't forget to copy the DLLs (see above) into the folder with the game before trying to run it.
