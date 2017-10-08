;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (Mac OS X x86_64)
;--------------------------------------------------------
	.module blinky
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _GPIO_WriteReverse
	.globl _GPIO_Init
	.globl _Delay
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ;reset
	int 0x0000 ;trap
	int 0x0000 ;int0
	int 0x0000 ;int1
	int 0x0000 ;int2
	int 0x0000 ;int3
	int 0x0000 ;int4
	int 0x0000 ;int5
	int 0x0000 ;int6
	int 0x0000 ;int7
	int 0x0000 ;int8
	int 0x0000 ;int9
	int 0x0000 ;int10
	int 0x0000 ;int11
	int 0x0000 ;int12
	int 0x0000 ;int13
	int 0x0000 ;int14
	int 0x0000 ;int15
	int 0x0000 ;int16
	int 0x0000 ;int17
	int 0x0000 ;int18
	int 0x0000 ;int19
	int 0x0000 ;int20
	int 0x0000 ;int21
	int 0x0000 ;int22
	int 0x0000 ;int23
	int 0x0000 ;int24
	int 0x0000 ;int25
	int 0x0000 ;int26
	int 0x0000 ;int27
	int 0x0000 ;int28
	int 0x0000 ;int29
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 55: void main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 59: GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
	push	#0xe0
	push	#0x20
	push	#0x05
	push	#0x50
	call	_GPIO_Init
	addw	sp, #4
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 61: while (1)
00102$:
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 64: GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
	push	#0x20
	push	#0x05
	push	#0x50
	call	_GPIO_WriteReverse
	addw	sp, #3
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 65: Delay(0xFFFF);
	push	#0xff
	push	#0xff
	call	_Delay
	popw	x
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 66: Delay(0xFFFF);
	push	#0xff
	push	#0xff
	call	_Delay
	popw	x
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 67: Delay(0xFFFF);
	push	#0xff
	push	#0xff
	call	_Delay
	popw	x
	jra	00102$
	ret
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 77: void Delay(uint16_t nCount)
;	-----------------------------------------
;	 function Delay
;	-----------------------------------------
_Delay:
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 80: while (nCount != 0)
	ldw	x, (0x03, sp)
00101$:
	tnzw	x
	jrne	00115$
	ret
00115$:
;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 82: nCount--;
	decw	x
	jra	00101$
	ret
	.area CODE
	.area INITIALIZER
	.area CABS (ABS)
