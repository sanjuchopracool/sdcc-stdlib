#ifndef COMMON_H
#define COMMON_H

#include <stm8s.h>
#include <stdlib.h>
#include <stdarg.h>

/* GPIO */
#define PA_ODR *(__IO uint8_t*)0x5000
#define PA_IDR *(__IO uint8_t*)0x5001
#define PA_DDR *(__IO uint8_t*)0x5002
#define PA_CR1 *(__IO uint8_t*)0x5003
#define PA_CR2 *(__IO uint8_t*)0x5004

#define PB_ODR *(__IO uint8_t*)0x5005
#define PB_IDR *(__IO uint8_t*)0x5006
#define PB_DDR *(__IO uint8_t*)0x5007
#define PB_CR1 *(__IO uint8_t*)0x5008
#define PB_CR2 *(__IO uint8_t*)0x5009

#define PC_ODR *(__IO uint8_t*)0x500A
#define PC_IDR *(__IO uint8_t*)0x500B
#define PC_DDR *(__IO uint8_t*)0x500C
#define PC_CR1 *(__IO uint8_t*)0x500D
#define PC_CR2 *(__IO uint8_t*)0x500E

#define PD_ODR *(__IO uint8_t*)0x500F
#define PD_IDR *(__IO uint8_t*)0x5010
#define PD_DDR *(__IO uint8_t*)0x5011
#define PD_CR1 *(__IO uint8_t*)0x5012
#define PD_CR2 *(__IO uint8_t*)0x5013

#define PE_ODR *(__IO uint8_t*)0x5014
#define PE_IDR *(__IO uint8_t*)0x5015
#define PE_DDR *(__IO uint8_t*)0x5016
#define PE_CR1 *(__IO uint8_t*)0x5017
#define PE_CR2 *(__IO uint8_t*)0x5018

#define PF_ODR *(__IO uint8_t*)0x5019
#define PF_IDR *(__IO uint8_t*)0x501A
#define PF_DDR *(__IO uint8_t*)0x501B
#define PF_CR1 *(__IO uint8_t*)0x501C
#define PF_CR2 *(__IO uint8_t*)0x501D

/*EXTI*/
#define EXTI_CR1        *(__IO uint8_t*)0x50A0
#define EXTI_CR2        *(__IO uint8_t*)0x50A1
///////////////////////////////////////////////////////////////////////////////
////////////////////// CLOCK set AT 16MHz HSI /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* CLOCK */
#define CLK_SWR 	*(__IO uint8_t*)0x50C4
#define CLK_SWCR	*(__IO uint8_t*)0x50C5
#define CLK_DIVR	*(__IO uint8_t*)0x50C6

#endif // COMMON_H
