# liboard
This repository contains the hardware and firmware files for the liboard.
For the app that connects the liboard to lichess see [limin](https://github.com/LanyonConrad/limin/).

## PCB
Single layer pcb designed with DesignSpark PCB.

###Features:
* Microchip BM71 bluetooth module
* TI MSP430 microcontroller (Spi-By-Wire pins are available on the usb port for programming)
* Battery Management
* 3.3V LDO Voltage Regulator
* 81 Reverse Mount LEDs
* 3 8-bit shift registers
* 1 8:1 MUX
* Over 80 0-ohm resistor jumpers due to the single layer constraint...


## Firmware
Code is written in C, compiled with [msp430 GCC](http://www.ti.com/tool/msp430-gcc-opensource), and programmed to chip with [MSPDebug](https://github.com/dlbeer/mspdebug) using the MSP430G2 LaunchPad ([MSP-EXP430G2](http://www.ti.com/tool/msp-exp430g2)).

## Todo
Add full bill of materials

## Assembly
This PCB is essentially one side of a membrane switch panel.
A base with 8 conductive strips must be attached appropriately.
