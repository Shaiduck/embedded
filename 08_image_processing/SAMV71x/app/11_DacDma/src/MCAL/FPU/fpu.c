/****************************************************************************************************/
/**
\file       fpu.c
\brief      MCAL abstraction level - Floating Point Unit initialization and configuration
\author     Abraham Tezmol
\version    1.0
\project    Tau 
\date       23/October/2016
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** dac function prototypes and definitions */
#include "fpu.h"
/** Core Instructions */
#include "core_cmInstr.h"

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/** Address for ARM CPACR */
#define ADDR_CPACR 0xE000ED88
/** CPACR Register */
#define REG_CPACR (*((volatile uint32_t *)ADDR_CPACR))

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Floating Point Unit Enable.
* \         The function enables the Floating Point Unit (coprocessor) embedded in Cortex M7
* \author   Abraham Tezmol
* \param    none
* \return   none
* \todo
*/
void vfnFpu_enable(void)
{
  irqflags_t flags;
  flags = cpu_irq_save();
  REG_CPACR |=  (0xFu << 20);
  __DSB();
  __ISB();
  cpu_irq_restore(flags);
}
