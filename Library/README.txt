
/**************************************************************/
  SMARTGPU2 ARDUINO UNO-MEGA-DUE LIBRARY V7.0 VIZIC TECHNOLOGIES 2020

This library help the user to communicate any SMARTGPU2 board with an arduino via the SmartSHIELD board.

*be sure to check pinout while mounting the SMARTSHIELD or the SMARTGPU2 LCD320x240 2.4" directly as shield.

Where to place this entire folder(SMARTGPU2)?

place it in the arduino C:/ installation folder path:

\arduino\libraries\SMARTGPU2

restart arduino IDE to recognize the library and enjoy!

---------------------IMPORTANT------------------------
Before using your smartGPU2 board, go to smartGPU2.h file and uncomment the proper line under "user modifable" section:

//If using smartGPU2 2.4" LCD320x240 mounted directly as arduino shield, please uncomment the next:
#define SMARTGPU2_24_DIRECT_SHIELD

//-SmartSHIELD uses default Arduino pin p4 for Reset, if another pin is soldered in the SmartSHIELD(pin 7, 8 or 13), please modify here:
//-SmartGPU2-Arduino RESET PIN definition 
#define SG_RESET 4       //Define for the RESET pin connected on the SmartSHIELD board(pin 7, 8 or 13) 

//-Arduino serial port and AREF configuration using smartSHIELD
#define SG_SERIALPORT     (Serial)

/**************************************************************/
Finally be sure to download all the SMARTGPU2 Arduino examples 100% ready to compile and load from our website

/**************************************************************/
SMARTGPU2 boards:
https://www.vizictechnologies.com/products

VIZIC TECHNOLOGIES Copyright 2020

www.vizictechnologies.com
/**************************************************************/
