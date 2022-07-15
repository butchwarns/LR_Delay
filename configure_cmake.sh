#! /bin/bash

# Allow this script to be run from different working directory without messing up relative paths
scriptdir="$(dirname "$0")"
cd "$scriptdir"

/home/butch/FRUT/prefix/FRUT/bin/Jucer2CMake reprojucer LR_Delay.jucer /home/butch/FRUT/prefix/FRUT/cmake/Reprojucer.cmake --juce-modules="/home/butch/JUCE/modules"
