# MKD51-Simulator
dll applicatiom for Keil, that simulates MKD51 peripherals

# Installation:
Copy all dlls and folders with dlls to Keil_v5/BIN directory.
!!! UPDATE!!! Copy the same files without MKD51_Plugin.dll to the Keil_v5/UV4 directory or else it will fail

In Keil:
->Options for target
->Debug
->Check Use simulator and Limit Speed to Real-Time
->next to dialog DLL there is a section parameter: (add -dMKD51_Plugin)

Notes:
Simulator does not work with all possible 8051 uC due to Keil bugs. As far tested only with intel's 8051
Currently only outputs are working properly (diodes, diodeL8, Buzzer, SEGS)
Sometimes Crashes xD (hope to solve it soon)
Timing strongly dependant to Keil and OS, so not perfect.
