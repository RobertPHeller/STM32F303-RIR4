# STM32F303-RIR4

STM32F303 Nucleo Baseboard for Aztrax RIR4 shield

This baseboard has Morpho sockets for a STM32F303 board (NUCLEO-F303K8), with 
one or two [Azatrax RIR4 
shields](https://www.azatrax.com/arduino-shield-ir-detector.html) stacked on 
top.  There is firmware that implements grade crossing logic:

1. LowRes12Tracks: low resolution mode, two sensors per track (1 or 2 tracks, 
one shield, unidirectional) ![Low resolution mode, two sensors per track (1 or 
2 tracks, one shield, 
unidirectional)](https://github.com/RobertPHeller/STM32F303-RIR4/blob/main/firmware/doc/images/LowRes12Tracks.png)
2. StandardRes1Track: standard resolution mode, four sensors per track (1 
track, one shield, bi-directional) ![Standard resolution mode, four sensors 
per track (1 track, one shield, 
bi-directional)](https://github.com/RobertPHeller/STM32F303-RIR4/blob/main/firmware/doc/images/StandardRes1Track.png)
3. StandardRes2Tracks: standard resolution mode, four sensors per track (2 
tracks, two shields, bi-directional) ![Standard resolution mode, four sensors 
per track (2 tracks, two shields, 
bi-directional)](https://github.com/RobertPHeller/STM32F303-RIR4/blob/main/firmware/doc/images/StandardRes2Tracks.png)

The grade crossing logic generates events for activate and deactivate.  These 
events need to be connected to outputs to do things like lower and raise 
gates, start/stop flashing lights, etc.

It is also possible to build the firmware to just expose the RIR4 directly, 
without grade crossing logic.

The baseboard adds additional I/O to help implement the grade crossing itself:

- 4 Blinking Signals: for the lights
- 2 Stall motors for gates or other things.
- 4 Servos for gates or other things.
- 2 Solid State Relays for other accessories (sound units, etc.)

