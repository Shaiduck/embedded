Overview
========
This application represents the "802.15.4 EndDevice" of the My Star Network Demo, and it demonstrates the following:
- scanning for a coordinator
- association procedure to a Personal Area Network (PAN)
- the data polling procedure.
To monitor the messages sent by this demo, the "MyStarNetwork Demo" PC application or console application can be used.
For more information please refer to the "IEEE 802.15.4 MAC Demo Applications User's Guide.pdf" document.

Toolchain supported
===================
- IAR embedded Workbench 7.70.1
- Kinetis Development Studio IDE 3.2.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K64F_FRDM-CR20A board
- Personal Computer with MyStarNetwork Demo application installed

Board settings
==============
No special board setting.

Prepare the Demo
================
1.  Connect a mini/micro USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Press the reset button, then any other switch button on your board to begin running the demo.

Running the demo
================
Use the "MyStarNetwork Demo" PC application, or follow the instruction displayed on the console.