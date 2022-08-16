# LR_Delay
[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.png?v=103)](https://github.com/ellerbrock/open-source-badges/)

A stereo delay plugin which emphasizes free (non beat-synced) controls for the individual channels. Built with [Faust](https://faust.grame.fr/) and [JUCE](https://juce.com/).

## Motivation
Delay effects always seemed kind of interesting to me, so when I wanted to see how possible it is to create an audio plugin with DSP written in Faust, it was naturally one of the choices. Also, I believe that delays have a much stronger effect in a musical context if they are not synced exactly to the beat or inbetween channels. 

## A word of caution
The project is currently in pre-release state and there might be breaking changes. I do my best to test everything, but the occasional bug can still find it's way into the plugin. Please don't hesitate to report bugs if you find some!

## Project status
Functional work in progress. The GUI will probably get an overhaul someday and I do intend to add more features in the future.  
A preset system as not yet been implemented.
 
## Screenshots
![LR_Delay v0.1.0 User Interface](/pictures/LR_Delay_GUI_small.jpg?raw=true "LR_Delay v0.1.0 User Interface")

## Tech/framework used
*LR_Delay* is an audio plugin written in **JUCE**, so it can be compiled into most formats like **VST3** or **AU**.  
The project is built with **CMake** ([FRUT](https://github.com/McMartin/FRUT) is used to translate the **Projucer** file to a CMake project).  
It should be built comfortably on **Linux**, **Mac** and **Windows** - I only have a Linux machine to test it on at the moment.  
DSP code is (almost) entirely written in the **Faust** programming language, which is then compiled to a C++ file to be used in our JUCE project.  
Some **bash** scripts automate different parts of the process to make life more easy.  

## Features
The plugin is a simple stereo delay with mostly separated controls for the individual channels.  
Some effects in the feedback loop allow for tonal shaping of the "wet" parts of the signal.  
By use of the *width* parameter, you can freely interpolate between a dual-mono (two taps) or a regular stereo.
The delay line doesn't change pitch when the delay time is modulated.  
Internal oversampling reduces aliasing from the feedback nonlinearity and helps with the virtaul analog filter responses.  
Very short delay times can create interesting timbres. (Be careful, as the output can get huge quickly!)

## Installation
Regardless of operating system, the plugin can be built by setting the correct exporter in the Projucer and then proceeding with the build as per the oficial JUCE instructions.

If you want to be using **Emacs/Vim**, **VSCode** or the like, you can use the supplied scripts to configure the CMake project after any changes were made through Projucer and then use one of the [CMake generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) to create a build system suiting your needs (free from clunky IDEs like Xcode or Visual Studio). See the `.sh` files for how this can be done in very few lines of terminal commands.

The project comes preconfigured for a unix-based system! Here you need to only invoke `configure_cmake.sh` to create an updated CMake project and subsequently run `builds_cmake/build_cmake.sh`, which generates a makefile, builds the plugin in VST3 format and then copies it to the correct system folder.  

If you make any changes to the Faust code the compilation script in the `dsp` directory can be used to generate the appropriate C++ header.  

## How to use?
Turn the knobs and listen..
All single controls on the left affect both channels. The dual controls are separated for L and R.

## What about Faust?
Faust is a great tool for writing music DSP code and integrates nicely with C++ projects, but it has its drawbacks. Prototyping is fast and easy with Faust and getting visual output in the form of block diagrams can be most helpful. You can create a working standalone app with user interface in no time. One of the biggest lacking features of the Faust language is multirate support. The LR_Delay plugin therefore runs the whole algorithm at an oversampled rate to reduce aliasing introduced by the nonlinearities. The Faust devs are well aware of this and language extensions have been proposed. (At the time of being this is still the only option though as far as I'm aware.) For more complex setups, the way to go I reckon is using multiple Faust DSP objects with surrounding C++ code.

## License
All JUCE code files are released under the GPLv3 license.
Faust code and it's generated C++ code file are licensed under the [MIT](https://opensource.org/licenses/MIT) license.
The Manrope font files are released under the SIL Open Font License, version 1.1.  

The graphics, my name any logos present are proprietary and fall under copyright.

Copyright © 2022 Butch Warns
