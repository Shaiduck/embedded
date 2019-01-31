/****************************************************************************************************/
/**
\file       typedefs.h
\brief      Variable types and common macros
\author     Abraham Tezmol
\version    1.0
\date       19/06/2016
*/
/****************************************************************************************************/

#ifndef TYPEDEFS_H        /*prevent duplicated includes*/ 
#define    TYPEDEFS_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of project wide TYPES
*****************************************************************************************************/


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
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

#ifndef NULL
  #define    NULL    ( ( void * ) 0 )
#endif

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

#endif                                     /* TYPEDEFS_H */ 