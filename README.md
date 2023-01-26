# SideTone Duplex
Portable C++ duplex voice capture and low latency feedback

https://github.com/type-one/SideToneDuplex

Other (higher) latency but more flexible versions are available at 
https://github.com/type-one/SideTone
https://github.com/type-one/CSideTone

# What
Small test program written in C++17 to have voice feedback with short latency. 
The code is portable and use the miniaudio framework (https://miniaud.io/).

# Why
The purpose was to test the duplex feature of miniaudio and which minimum period
it was possible to reach (1 ms).

This small framework can be a start for more complex sound processing on the feedback voice.

# How
Can be compiled and Linux and Windows, and should be easily
adapted for other platforms supported by miniaudio (Mac, Android, BSD).

The underlying miniaudio uses the standard default sound API of the OS (Linux/ALSA, Windows/WinMM, 
Android/OpenSLES, Mac/CoreAudio...) and not a specific low latency one (Jack, ASIO, ...),
with default parameters.

On Linux, just use cmake .
On Windows, just use cmake-gui to generate a Visual Studio solution

Tested on Windows 10 and Ubuntu/Debian Linux (on native host and in VMplayer).
It should work also on Raspberry Pi.
It just use default capture and playback devices.

Launch in a shell using "sidetone_duplex.exe" or "sidetone_duplex"
Press "enter" to exit

You can play with different parameters in the audio/audio_config.hpp
file: format, sample rate, channels, period.

Recommended parameters are 22050 hz, mono (1 channel), signed 16, and a period of 1 ms.

Enjoy

# Author
Laurent Lardinois / Type One (TFL-TDV)

https://be.linkedin.com/in/laurentlardinois

https://demozoo.org/sceners/19691/
