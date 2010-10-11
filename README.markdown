Homebrew toolchain/sdk/samples for the Samsung YP-Q2 PMP
========================================================

Based on Sigmatel (now Freescale) STMP3700 SoC, has an ARM cpu ()
and a DSP for accelerated video/audio decoding, everything wrapped
up nicely with a Linux system.
The update (Q2Update.dat) format and encryption has been reversed
and a repacker has been made, making custom firmwares possible.
The most common hack (and the one im using) is unpacking the fw with
the unpack.sh script (in the tools folder) and editing the file
'runusb.sh' into the 'appfs/bin folder and adding a line that executes
a file off /mnt/usb (the partition seen when connected to the pc) like

/mnt/usb/myscript.sh

Repacking the update with repack.sh and flashing the HACK.dat file is
all you need to start enjoying homebrews on your Q2 :D

### USB script ###

Youre not an unix guru and you dont know what to write into the myscript.sh ?
Don't worry, just copy this :

[#!/bin/sh
sleep 10
if [ -f /mnt/usb/runcode ]; then
    rm -f /mnt/usb/runcode
    killall -9 AppMain
    sleep 6
    /mnt/usb/hello
fi]

It basically waits 10 seconds, then if a file called runcode exists into the
root it will kill the main player app and start your app called 'hello' (yep,
it must be placed in the root too)

### SDK ###

Want to start coding on this pocket beast? :D
Just download or build an ARM compiler ([Codesourcery][armtk] offers a
precompiled one) and start reading out the hello world code to start grasping
how the libQ2 works

libQ2 is going to be reorganized in a better way as soon as i get all the basic
stuff working.

### What works... ###

- Video trough framebuffer
- Input (need multiple keys catching support)
- Keypad leds control
- Brightness adjusting
- CPU clock setting

### ...and what doesnt ###

- Touchpad
- RTC interface
- Sound (need to reverse the 'diagnosis' bin to document how /dev/dsp works)
- USB system
- Earphones detection
- Maybe something i forgot :D

### Creditz ###

Matt_P for suggesting me the idea that the update was xor cyphered,
Booto for being the unix guru,
HACKERCHANNEL for being the greatest dudes on teh world,
Mum and Dad for buying me this wonderful PMP as b-day surprise :)


[armtk]: http://www.codesourcery.com/sgpp/lite/arm/portal/release1294

The Lemon Man   (C) 2010
HACKERCHANNEL   (c) 2010
