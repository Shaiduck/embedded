/****************************************************************************************************/
/**
\file       Std_Types.h
\brief      Standard Type Definitions based on AUTOSAR_SWS_StandardTypes
\author     Francisco Martinez
\version    1.0
\date       19/08/2018
*/
/****************************************************************************************************/

#ifndef STD_TYPES_H        /*prevent duplicated includes*/ 
#define STD_TYPES_H    

	/*****************************************************************************************************
	* Include files
	*****************************************************************************************************/
  /** Main group of includes for board definitions, chip definitions and type definitions */
  #include "board.h"
  #include <stdbool.h>
  #include <stdio.h>
  /** Compiler */
	#include "compiler.h"
  /** Core-specific prototypes and definitions */
	#include "core_cm7.h"
	/** Definitions of System Clock Frequency (Core Clock) */
	#include "system_samv71.h"

	/*****************************************************************************************************
	* Declaration of project wide TYPES
	*****************************************************************************************************/

	typedef uint8_t Std_ReturnType;

	#ifndef STATUSTYPEDEFINED
		#define STATUSTYPEDEFINED
		#define E_OK     (Std_ReturnType)0x00
		#define E_NOT_OK (Std_ReturnType)0x01
	#endif

	#define STD_HIGH    0x01 /* Physical state 5V or 3.3V */
	#define STD_LOW     0x00 /* Physical state 0V */
	#define STD_ACTIVE  0x01 /* Logical state active */
	#define STD_IDLE    0x00 /* Logical state idle */
	#define STD_ON      0x01
	#define STD_OFF     0x00

	#ifndef NULL
		#define    NULL    ( ( void * ) 0 )
	#endif

#endif  /* STD_TYPES_H */ 