#! /bin/bash
rm -rf delay-svg/
faust -i -svg -a faustMinimal.h delay.dsp -cn Delay -o  delay.h -double
cp delay.h ../Source/
