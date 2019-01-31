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
  /** Definitions of samv71 registers*/
  #include "samv71.h"

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
#define UINT8 	__attribute__	((aligned (1))) uint8_t
#define UINT16 	__attribute__	((aligned (2))) uint16_t
#define UINT32 	__attribute__	((aligned (4))) uint32_t

#define INT8	__attribute__  	((aligned (1))) int8_t
#define INT16 	__attribute__ 	((aligned (2))) int16_t
#define INT32 	__attribute__ 	((aligned (4))) int32_t


#define VUINT8 	__attribute__ 	((aligned (1))) volatile uint8_t
#define VUINT16 __attribute__	((aligned (2))) volatile uint16_t
#define VUINT32 __attribute__	((aligned (4))) volatile uint32_t

#define VINT8 	__attribute__  	((aligned (1))) volatile int8_t
#define VINT16 	__attribute__ 	((aligned (2))) volatile int16_t
#define VINT32 	__attribute__ 	((aligned (4))) volatile int32_t

typedef  void  ( * tPtr_to_function )( void );
  #ifndef NULL
		#define    NULL    ( ( void * ) 0 )
  #endif

#endif  /* STD_TYPES_H */ 