                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.6.0 #9615 (Mac OS X x86_64)
                                      4 ;--------------------------------------------------------
                                      5 	.module stm8s_gpio
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _GPIO_DeInit
                                     12 	.globl _GPIO_Init
                                     13 	.globl _GPIO_Write
                                     14 	.globl _GPIO_WriteHigh
                                     15 	.globl _GPIO_WriteLow
                                     16 	.globl _GPIO_WriteReverse
                                     17 	.globl _GPIO_ReadOutputData
                                     18 	.globl _GPIO_ReadInputData
                                     19 	.globl _GPIO_ReadInputPin
                                     20 	.globl _GPIO_ExternalPullUpConfig
                                     21 ;--------------------------------------------------------
                                     22 ; ram data
                                     23 ;--------------------------------------------------------
                                     24 	.area DATA
                                     25 ;--------------------------------------------------------
                                     26 ; ram data
                                     27 ;--------------------------------------------------------
                                     28 	.area INITIALIZED
                                     29 ;--------------------------------------------------------
                                     30 ; absolute external ram data
                                     31 ;--------------------------------------------------------
                                     32 	.area DABS (ABS)
                                     33 ;--------------------------------------------------------
                                     34 ; global & static initialisations
                                     35 ;--------------------------------------------------------
                                     36 	.area HOME
                                     37 	.area GSINIT
                                     38 	.area GSFINAL
                                     39 	.area GSINIT
                                     40 ;--------------------------------------------------------
                                     41 ; Home
                                     42 ;--------------------------------------------------------
                                     43 	.area HOME
                                     44 	.area HOME
                                     45 ;--------------------------------------------------------
                                     46 ; code
                                     47 ;--------------------------------------------------------
                                     48 	.area CODE
                                     49 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 53: void GPIO_DeInit(GPIO_TypeDef* GPIOx)
                                     50 ;	-----------------------------------------
                                     51 ;	 function GPIO_DeInit
                                     52 ;	-----------------------------------------
      0080DD                         53 _GPIO_DeInit:
      0080DD 89               [ 2]   54 	pushw	x
                                     55 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 55: GPIOx->ODR = GPIO_ODR_RESET_VALUE; /* Reset Output Data Register */
      0080DE 16 05            [ 2]   56 	ldw	y, (0x05, sp)
      0080E0 17 01            [ 2]   57 	ldw	(0x01, sp), y
      0080E2 1E 01            [ 2]   58 	ldw	x, (0x01, sp)
      0080E4 7F               [ 1]   59 	clr	(x)
                                     60 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 56: GPIOx->DDR = GPIO_DDR_RESET_VALUE; /* Reset Data Direction Register */
      0080E5 1E 01            [ 2]   61 	ldw	x, (0x01, sp)
      0080E7 5C               [ 2]   62 	incw	x
      0080E8 5C               [ 2]   63 	incw	x
      0080E9 7F               [ 1]   64 	clr	(x)
                                     65 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 57: GPIOx->CR1 = GPIO_CR1_RESET_VALUE; /* Reset Control Register 1 */
      0080EA 1E 01            [ 2]   66 	ldw	x, (0x01, sp)
      0080EC 1C 00 03         [ 2]   67 	addw	x, #0x0003
      0080EF 7F               [ 1]   68 	clr	(x)
                                     69 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 58: GPIOx->CR2 = GPIO_CR2_RESET_VALUE; /* Reset Control Register 2 */
      0080F0 1E 01            [ 2]   70 	ldw	x, (0x01, sp)
      0080F2 1C 00 04         [ 2]   71 	addw	x, #0x0004
      0080F5 7F               [ 1]   72 	clr	(x)
      0080F6 85               [ 2]   73 	popw	x
      0080F7 81               [ 4]   74 	ret
                                     75 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 71: void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode)
                                     76 ;	-----------------------------------------
                                     77 ;	 function GPIO_Init
                                     78 ;	-----------------------------------------
      0080F8                         79 _GPIO_Init:
      0080F8 52 05            [ 2]   80 	sub	sp, #5
                                     81 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 81: GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
      0080FA 16 08            [ 2]   82 	ldw	y, (0x08, sp)
      0080FC 17 04            [ 2]   83 	ldw	(0x04, sp), y
      0080FE 1E 04            [ 2]   84 	ldw	x, (0x04, sp)
      008100 1C 00 04         [ 2]   85 	addw	x, #0x0004
      008103 1F 01            [ 2]   86 	ldw	(0x01, sp), x
      008105 1E 01            [ 2]   87 	ldw	x, (0x01, sp)
      008107 F6               [ 1]   88 	ld	a, (x)
      008108 88               [ 1]   89 	push	a
      008109 7B 0B            [ 1]   90 	ld	a, (0x0b, sp)
      00810B 43               [ 1]   91 	cpl	a
      00810C 6B 04            [ 1]   92 	ld	(0x04, sp), a
      00810E 84               [ 1]   93 	pop	a
      00810F 14 03            [ 1]   94 	and	a, (0x03, sp)
      008111 1E 01            [ 2]   95 	ldw	x, (0x01, sp)
      008113 F7               [ 1]   96 	ld	(x), a
                                     97 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 98: GPIOx->DDR |= (uint8_t)GPIO_Pin;
      008114 1E 04            [ 2]   98 	ldw	x, (0x04, sp)
      008116 5C               [ 2]   99 	incw	x
      008117 5C               [ 2]  100 	incw	x
                                    101 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 87: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x80) != (uint8_t)0x00) /* Output mode */
      008118 0D 0B            [ 1]  102 	tnz	(0x0b, sp)
      00811A 2A 20            [ 1]  103 	jrpl	00105$
                                    104 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 91: GPIOx->ODR |= (uint8_t)GPIO_Pin;
      00811C 16 04            [ 2]  105 	ldw	y, (0x04, sp)
      00811E 90 F6            [ 1]  106 	ld	a, (y)
                                    107 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 89: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x10) != (uint8_t)0x00) /* High level */
      008120 88               [ 1]  108 	push	a
      008121 7B 0C            [ 1]  109 	ld	a, (0x0c, sp)
      008123 A5 10            [ 1]  110 	bcp	a, #0x10
      008125 84               [ 1]  111 	pop	a
      008126 27 08            [ 1]  112 	jreq	00102$
                                    113 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 91: GPIOx->ODR |= (uint8_t)GPIO_Pin;
      008128 1A 0A            [ 1]  114 	or	a, (0x0a, sp)
      00812A 16 04            [ 2]  115 	ldw	y, (0x04, sp)
      00812C 90 F7            [ 1]  116 	ld	(y), a
      00812E 20 06            [ 2]  117 	jra	00103$
      008130                        118 00102$:
                                    119 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 95: GPIOx->ODR &= (uint8_t)(~(GPIO_Pin));
      008130 14 03            [ 1]  120 	and	a, (0x03, sp)
      008132 16 04            [ 2]  121 	ldw	y, (0x04, sp)
      008134 90 F7            [ 1]  122 	ld	(y), a
      008136                        123 00103$:
                                    124 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 98: GPIOx->DDR |= (uint8_t)GPIO_Pin;
      008136 F6               [ 1]  125 	ld	a, (x)
      008137 1A 0A            [ 1]  126 	or	a, (0x0a, sp)
      008139 F7               [ 1]  127 	ld	(x), a
      00813A 20 04            [ 2]  128 	jra	00106$
      00813C                        129 00105$:
                                    130 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 103: GPIOx->DDR &= (uint8_t)(~(GPIO_Pin));
      00813C F6               [ 1]  131 	ld	a, (x)
      00813D 14 03            [ 1]  132 	and	a, (0x03, sp)
      00813F F7               [ 1]  133 	ld	(x), a
      008140                        134 00106$:
                                    135 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 112: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      008140 1E 04            [ 2]  136 	ldw	x, (0x04, sp)
      008142 1C 00 03         [ 2]  137 	addw	x, #0x0003
                                    138 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 110: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x40) != (uint8_t)0x00) /* Pull-Up or Push-Pull */
      008145 7B 0B            [ 1]  139 	ld	a, (0x0b, sp)
      008147 A5 40            [ 1]  140 	bcp	a, #0x40
      008149 27 06            [ 1]  141 	jreq	00108$
                                    142 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 112: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      00814B F6               [ 1]  143 	ld	a, (x)
      00814C 1A 0A            [ 1]  144 	or	a, (0x0a, sp)
      00814E F7               [ 1]  145 	ld	(x), a
      00814F 20 04            [ 2]  146 	jra	00109$
      008151                        147 00108$:
                                    148 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 116: GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
      008151 F6               [ 1]  149 	ld	a, (x)
      008152 14 03            [ 1]  150 	and	a, (0x03, sp)
      008154 F7               [ 1]  151 	ld	(x), a
      008155                        152 00109$:
                                    153 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 123: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x20) != (uint8_t)0x00) /* Interrupt or Slow slope */
      008155 7B 0B            [ 1]  154 	ld	a, (0x0b, sp)
      008157 A5 20            [ 1]  155 	bcp	a, #0x20
      008159 27 0A            [ 1]  156 	jreq	00111$
                                    157 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 125: GPIOx->CR2 |= (uint8_t)GPIO_Pin;
      00815B 1E 01            [ 2]  158 	ldw	x, (0x01, sp)
      00815D F6               [ 1]  159 	ld	a, (x)
      00815E 1A 0A            [ 1]  160 	or	a, (0x0a, sp)
      008160 1E 01            [ 2]  161 	ldw	x, (0x01, sp)
      008162 F7               [ 1]  162 	ld	(x), a
      008163 20 08            [ 2]  163 	jra	00113$
      008165                        164 00111$:
                                    165 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 129: GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
      008165 1E 01            [ 2]  166 	ldw	x, (0x01, sp)
      008167 F6               [ 1]  167 	ld	a, (x)
      008168 14 03            [ 1]  168 	and	a, (0x03, sp)
      00816A 1E 01            [ 2]  169 	ldw	x, (0x01, sp)
      00816C F7               [ 1]  170 	ld	(x), a
      00816D                        171 00113$:
      00816D 5B 05            [ 2]  172 	addw	sp, #5
      00816F 81               [ 4]  173 	ret
                                    174 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 141: void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t PortVal)
                                    175 ;	-----------------------------------------
                                    176 ;	 function GPIO_Write
                                    177 ;	-----------------------------------------
      008170                        178 _GPIO_Write:
                                    179 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 143: GPIOx->ODR = PortVal;
      008170 1E 03            [ 2]  180 	ldw	x, (0x03, sp)
      008172 7B 05            [ 1]  181 	ld	a, (0x05, sp)
      008174 F7               [ 1]  182 	ld	(x), a
      008175 81               [ 4]  183 	ret
                                    184 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 154: void GPIO_WriteHigh(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    185 ;	-----------------------------------------
                                    186 ;	 function GPIO_WriteHigh
                                    187 ;	-----------------------------------------
      008176                        188 _GPIO_WriteHigh:
                                    189 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 156: GPIOx->ODR |= (uint8_t)PortPins;
      008176 1E 03            [ 2]  190 	ldw	x, (0x03, sp)
      008178 F6               [ 1]  191 	ld	a, (x)
      008179 1A 05            [ 1]  192 	or	a, (0x05, sp)
      00817B F7               [ 1]  193 	ld	(x), a
      00817C 81               [ 4]  194 	ret
                                    195 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 167: void GPIO_WriteLow(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    196 ;	-----------------------------------------
                                    197 ;	 function GPIO_WriteLow
                                    198 ;	-----------------------------------------
      00817D                        199 _GPIO_WriteLow:
      00817D 88               [ 1]  200 	push	a
                                    201 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 169: GPIOx->ODR &= (uint8_t)(~PortPins);
      00817E 1E 04            [ 2]  202 	ldw	x, (0x04, sp)
      008180 F6               [ 1]  203 	ld	a, (x)
      008181 6B 01            [ 1]  204 	ld	(0x01, sp), a
      008183 7B 06            [ 1]  205 	ld	a, (0x06, sp)
      008185 43               [ 1]  206 	cpl	a
      008186 14 01            [ 1]  207 	and	a, (0x01, sp)
      008188 F7               [ 1]  208 	ld	(x), a
      008189 84               [ 1]  209 	pop	a
      00818A 81               [ 4]  210 	ret
                                    211 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 180: void GPIO_WriteReverse(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    212 ;	-----------------------------------------
                                    213 ;	 function GPIO_WriteReverse
                                    214 ;	-----------------------------------------
      00818B                        215 _GPIO_WriteReverse:
                                    216 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 182: GPIOx->ODR ^= (uint8_t)PortPins;
      00818B 1E 03            [ 2]  217 	ldw	x, (0x03, sp)
      00818D F6               [ 1]  218 	ld	a, (x)
      00818E 18 05            [ 1]  219 	xor	a, (0x05, sp)
      008190 F7               [ 1]  220 	ld	(x), a
      008191 81               [ 4]  221 	ret
                                    222 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 191: uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
                                    223 ;	-----------------------------------------
                                    224 ;	 function GPIO_ReadOutputData
                                    225 ;	-----------------------------------------
      008192                        226 _GPIO_ReadOutputData:
                                    227 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 193: return ((uint8_t)GPIOx->ODR);
      008192 1E 03            [ 2]  228 	ldw	x, (0x03, sp)
      008194 F6               [ 1]  229 	ld	a, (x)
      008195 81               [ 4]  230 	ret
                                    231 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 202: uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
                                    232 ;	-----------------------------------------
                                    233 ;	 function GPIO_ReadInputData
                                    234 ;	-----------------------------------------
      008196                        235 _GPIO_ReadInputData:
                                    236 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 204: return ((uint8_t)GPIOx->IDR);
      008196 1E 03            [ 2]  237 	ldw	x, (0x03, sp)
      008198 E6 01            [ 1]  238 	ld	a, (0x1, x)
      00819A 81               [ 4]  239 	ret
                                    240 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 213: BitStatus GPIO_ReadInputPin(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
                                    241 ;	-----------------------------------------
                                    242 ;	 function GPIO_ReadInputPin
                                    243 ;	-----------------------------------------
      00819B                        244 _GPIO_ReadInputPin:
                                    245 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 215: return ((BitStatus)(GPIOx->IDR & (uint8_t)GPIO_Pin));
      00819B 1E 03            [ 2]  246 	ldw	x, (0x03, sp)
      00819D E6 01            [ 1]  247 	ld	a, (0x1, x)
      00819F 14 05            [ 1]  248 	and	a, (0x05, sp)
      0081A1 81               [ 4]  249 	ret
                                    250 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 225: void GPIO_ExternalPullUpConfig(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, FunctionalState NewState)
                                    251 ;	-----------------------------------------
                                    252 ;	 function GPIO_ExternalPullUpConfig
                                    253 ;	-----------------------------------------
      0081A2                        254 _GPIO_ExternalPullUpConfig:
      0081A2 88               [ 1]  255 	push	a
                                    256 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 233: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      0081A3 1E 04            [ 2]  257 	ldw	x, (0x04, sp)
      0081A5 1C 00 03         [ 2]  258 	addw	x, #0x0003
                                    259 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 231: if (NewState != DISABLE) /* External Pull-Up Set*/
      0081A8 0D 07            [ 1]  260 	tnz	(0x07, sp)
      0081AA 27 06            [ 1]  261 	jreq	00102$
                                    262 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 233: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      0081AC F6               [ 1]  263 	ld	a, (x)
      0081AD 1A 06            [ 1]  264 	or	a, (0x06, sp)
      0081AF F7               [ 1]  265 	ld	(x), a
      0081B0 20 09            [ 2]  266 	jra	00104$
      0081B2                        267 00102$:
                                    268 ;	/Users/sanju/Downloads/STM8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c: 236: GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
      0081B2 F6               [ 1]  269 	ld	a, (x)
      0081B3 6B 01            [ 1]  270 	ld	(0x01, sp), a
      0081B5 7B 06            [ 1]  271 	ld	a, (0x06, sp)
      0081B7 43               [ 1]  272 	cpl	a
      0081B8 14 01            [ 1]  273 	and	a, (0x01, sp)
      0081BA F7               [ 1]  274 	ld	(x), a
      0081BB                        275 00104$:
      0081BB 84               [ 1]  276 	pop	a
      0081BC 81               [ 4]  277 	ret
                                    278 	.area CODE
                                    279 	.area INITIALIZER
                                    280 	.area CABS (ABS)
