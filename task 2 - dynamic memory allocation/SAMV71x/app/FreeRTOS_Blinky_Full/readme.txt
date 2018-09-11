This file describes how to use the Atmel SAMV71 FreeRTOS project:

This example was created and test using the following envrionment:
-IDE: winIDEA/winIDEA Open
-Compiler: arm-none-eabi version 4.9.3 or higher
-Target HW: SAMV7 Xplained Ultra

Requirements:
- Debug HW: Onboard CMSIS-DAP, iSYSTEM iTag50
- Atmel SAMV71 Xplained Kit

Function:

FreeRTOS project which can be configured to either run a simple
Blinky demo using an RX and TX ask as well as queue to communicate
between the tasks or a comprehensive test/demo application.

Separate project workspaces have been created to directly run
either the blinky or the demo project (see below).


Project directory structure:

\---Atmel
    \---SAMV7x 
        \---SAMV71x
            +---app
            |   \---FreeRTOS_Blinky_Full
            |       +---src
            |       \---SAMV71_Xplained_Ultra
            |           \---Debug
			|
			+---bsp
			|   +---libboard_samv7_ek
            |   
            +---hal
            |   +---libchip_samv7
			|   \---utils
            |
			+---os
			|   \FreeRTOS_<rev>
			|
            \---toolset
                \---gcc

Project specific source/header files:

    - main.c                             Main program file
	- main_blinky.c                      Blinky example implementation
	- main_full.c                        Full Demo implementation
	- FreeRTOSConfig.h	                 FreeRTOS OS config file
	- RegTest.c                          Full Demo CPU reg test

In order to use the example program, perform the following steps:

 + winIDEA
    - Open one of the following preconfigured project workspaces:
         - FreeRTOS_Blinky_gcc_itag50.xjrf (iSYSTEM iTag50) 
		 - FreeRTOS_Demo_gcc_itag50.xjrf (iSYSTEM iTag50)
      under File->Workspace->Open_Workspace 
    - Rebuild all files: Project->Rebuild (optional)
    - Load project image: Debug->Download
    - Run program: Debug->Run Control->Run (F5)