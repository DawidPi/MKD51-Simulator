# MKD51-Simulator
dll applicatiom for Keil, that simulates MKD51 peripherals

# Installation: !!UPDATE!!
Copy all dlls and folders with dlls the Keil_v5/UV4 directory.
copy MKD51_Plugin.dll to Keil_v5/BIN directory

In Keil:
->Options for target

->Debug

->Check Use simulator and Limit Speed to Real-Time

->next to dialog DLL there is a section parameter: (add "-dMKD51_Plugin" <without quotes>)

->launch: (debug mode) peripherals->MKD51

Notes:
Simulator does not work with all possible 8051 uC due to Keil bugs. As far tested only with intel's 8051
Currently only outputs are working properly (diodes, diodeL8, Buzzer, SEGS)
Sometimes Crashes xD (hope to solve it soon)
Timing strongly dependant to Keil and OS, so not perfect.
