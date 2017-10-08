                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.6.0 #9615 (Mac OS X x86_64)
                                      4 ;--------------------------------------------------------
                                      5 	.module blinky
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _GPIO_WriteReverse
                                     13 	.globl _GPIO_Init
                                     14 	.globl _Delay
                                     15 ;--------------------------------------------------------
                                     16 ; ram data
                                     17 ;--------------------------------------------------------
                                     18 	.area DATA
                                     19 ;--------------------------------------------------------
                                     20 ; ram data
                                     21 ;--------------------------------------------------------
                                     22 	.area INITIALIZED
                                     23 ;--------------------------------------------------------
                                     24 ; Stack segment in internal ram 
                                     25 ;--------------------------------------------------------
                                     26 	.area	SSEG
      000001                         27 __start__stack:
      000001                         28 	.ds	1
                                     29 
                                     30 ;--------------------------------------------------------
                                     31 ; absolute external ram data
                                     32 ;--------------------------------------------------------
                                     33 	.area DABS (ABS)
                                     34 ;--------------------------------------------------------
                                     35 ; interrupt vector 
                                     36 ;--------------------------------------------------------
                                     37 	.area HOME
      008000                         38 __interrupt_vect:
      008000 82 00 80 83             39 	int s_GSINIT ;reset
      008004 82 00 00 00             40 	int 0x0000 ;trap
      008008 82 00 00 00             41 	int 0x0000 ;int0
      00800C 82 00 00 00             42 	int 0x0000 ;int1
      008010 82 00 00 00             43 	int 0x0000 ;int2
      008014 82 00 00 00             44 	int 0x0000 ;int3
      008018 82 00 00 00             45 	int 0x0000 ;int4
      00801C 82 00 00 00             46 	int 0x0000 ;int5
      008020 82 00 00 00             47 	int 0x0000 ;int6
      008024 82 00 00 00             48 	int 0x0000 ;int7
      008028 82 00 00 00             49 	int 0x0000 ;int8
      00802C 82 00 00 00             50 	int 0x0000 ;int9
      008030 82 00 00 00             51 	int 0x0000 ;int10
      008034 82 00 00 00             52 	int 0x0000 ;int11
      008038 82 00 00 00             53 	int 0x0000 ;int12
      00803C 82 00 00 00             54 	int 0x0000 ;int13
      008040 82 00 00 00             55 	int 0x0000 ;int14
      008044 82 00 00 00             56 	int 0x0000 ;int15
      008048 82 00 00 00             57 	int 0x0000 ;int16
      00804C 82 00 00 00             58 	int 0x0000 ;int17
      008050 82 00 00 00             59 	int 0x0000 ;int18
      008054 82 00 00 00             60 	int 0x0000 ;int19
      008058 82 00 00 00             61 	int 0x0000 ;int20
      00805C 82 00 00 00             62 	int 0x0000 ;int21
      008060 82 00 00 00             63 	int 0x0000 ;int22
      008064 82 00 00 00             64 	int 0x0000 ;int23
      008068 82 00 00 00             65 	int 0x0000 ;int24
      00806C 82 00 00 00             66 	int 0x0000 ;int25
      008070 82 00 00 00             67 	int 0x0000 ;int26
      008074 82 00 00 00             68 	int 0x0000 ;int27
      008078 82 00 00 00             69 	int 0x0000 ;int28
      00807C 82 00 00 00             70 	int 0x0000 ;int29
                                     71 ;--------------------------------------------------------
                                     72 ; global & static initialisations
                                     73 ;--------------------------------------------------------
                                     74 	.area HOME
                                     75 	.area GSINIT
                                     76 	.area GSFINAL
                                     77 	.area GSINIT
      008083                         78 __sdcc_gs_init_startup:
      008083                         79 __sdcc_init_data:
                                     80 ; stm8_genXINIT() start
      008083 AE 00 00         [ 2]   81 	ldw x, #l_DATA
      008086 27 07            [ 1]   82 	jreq	00002$
      008088                         83 00001$:
      008088 72 4F 00 00      [ 1]   84 	clr (s_DATA - 1, x)
      00808C 5A               [ 2]   85 	decw x
      00808D 26 F9            [ 1]   86 	jrne	00001$
      00808F                         87 00002$:
      00808F AE 00 00         [ 2]   88 	ldw	x, #l_INITIALIZER
      008092 27 09            [ 1]   89 	jreq	00004$
      008094                         90 00003$:
      008094 D6 81 BC         [ 1]   91 	ld	a, (s_INITIALIZER - 1, x)
      008097 D7 00 00         [ 1]   92 	ld	(s_INITIALIZED - 1, x), a
      00809A 5A               [ 2]   93 	decw	x
      00809B 26 F7            [ 1]   94 	jrne	00003$
      00809D                         95 00004$:
                                     96 ; stm8_genXINIT() end
                                     97 	.area GSFINAL
      00809D CC 80 80         [ 2]   98 	jp	__sdcc_program_startup
                                     99 ;--------------------------------------------------------
                                    100 ; Home
                                    101 ;--------------------------------------------------------
                                    102 	.area HOME
                                    103 	.area HOME
      008080                        104 __sdcc_program_startup:
      008080 CC 80 A0         [ 2]  105 	jp	_main
                                    106 ;	return from main will return to caller
                                    107 ;--------------------------------------------------------
                                    108 ; code
                                    109 ;--------------------------------------------------------
                                    110 	.area CODE
                                    111 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 55: void main(void)
                                    112 ;	-----------------------------------------
                                    113 ;	 function main
                                    114 ;	-----------------------------------------
      0080A0                        115 _main:
                                    116 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 59: GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
      0080A0 4B E0            [ 1]  117 	push	#0xe0
      0080A2 4B 20            [ 1]  118 	push	#0x20
      0080A4 4B 05            [ 1]  119 	push	#0x05
      0080A6 4B 50            [ 1]  120 	push	#0x50
      0080A8 CD 80 F8         [ 4]  121 	call	_GPIO_Init
      0080AB 5B 04            [ 2]  122 	addw	sp, #4
                                    123 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 61: while (1)
      0080AD                        124 00102$:
                                    125 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 64: GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
      0080AD 4B 20            [ 1]  126 	push	#0x20
      0080AF 4B 05            [ 1]  127 	push	#0x05
      0080B1 4B 50            [ 1]  128 	push	#0x50
      0080B3 CD 81 8B         [ 4]  129 	call	_GPIO_WriteReverse
      0080B6 5B 03            [ 2]  130 	addw	sp, #3
                                    131 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 65: Delay(0xFFFF);
      0080B8 4B FF            [ 1]  132 	push	#0xff
      0080BA 4B FF            [ 1]  133 	push	#0xff
      0080BC CD 80 D3         [ 4]  134 	call	_Delay
      0080BF 85               [ 2]  135 	popw	x
                                    136 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 66: Delay(0xFFFF);
      0080C0 4B FF            [ 1]  137 	push	#0xff
      0080C2 4B FF            [ 1]  138 	push	#0xff
      0080C4 CD 80 D3         [ 4]  139 	call	_Delay
      0080C7 85               [ 2]  140 	popw	x
                                    141 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 67: Delay(0xFFFF);
      0080C8 4B FF            [ 1]  142 	push	#0xff
      0080CA 4B FF            [ 1]  143 	push	#0xff
      0080CC CD 80 D3         [ 4]  144 	call	_Delay
      0080CF 85               [ 2]  145 	popw	x
      0080D0 20 DB            [ 2]  146 	jra	00102$
      0080D2 81               [ 4]  147 	ret
                                    148 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 77: void Delay(uint16_t nCount)
                                    149 ;	-----------------------------------------
                                    150 ;	 function Delay
                                    151 ;	-----------------------------------------
      0080D3                        152 _Delay:
                                    153 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 80: while (nCount != 0)
      0080D3 1E 03            [ 2]  154 	ldw	x, (0x03, sp)
      0080D5                        155 00101$:
      0080D5 5D               [ 2]  156 	tnzw	x
      0080D6 26 01            [ 1]  157 	jrne	00115$
      0080D8 81               [ 4]  158 	ret
      0080D9                        159 00115$:
                                    160 ;	/Users/sanju/Downloads/STM8/STM8S_SPL/blinky.c: 82: nCount--;
      0080D9 5A               [ 2]  161 	decw	x
      0080DA 20 F9            [ 2]  162 	jra	00101$
      0080DC 81               [ 4]  163 	ret
                                    164 	.area CODE
                                    165 	.area INITIALIZER
                                    166 	.area CABS (ABS)
