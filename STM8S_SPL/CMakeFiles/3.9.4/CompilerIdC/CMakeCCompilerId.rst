                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.6.0 #9615 (Mac OS X x86_64)
                                      4 ;--------------------------------------------------------
                                      5 	.module CMakeCCompilerId
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main_PARM_2
                                     12 	.globl _info_version
                                     13 	.globl _main
                                     14 	.globl _info_language_dialect_default
                                     15 	.globl _info_arch
                                     16 	.globl _info_platform
                                     17 	.globl _info_compiler
                                     18 ;--------------------------------------------------------
                                     19 ; special function registers
                                     20 ;--------------------------------------------------------
                                     21 	.area RSEG    (ABS,DATA)
      000000                         22 	.org 0x0000
                                     23 ;--------------------------------------------------------
                                     24 ; special function bits
                                     25 ;--------------------------------------------------------
                                     26 	.area RSEG    (ABS,DATA)
      000000                         27 	.org 0x0000
                                     28 ;--------------------------------------------------------
                                     29 ; overlayable register banks
                                     30 ;--------------------------------------------------------
                                     31 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                         32 	.ds 8
                                     33 ;--------------------------------------------------------
                                     34 ; internal ram data
                                     35 ;--------------------------------------------------------
                                     36 	.area DSEG    (DATA)
      000008                         37 _info_compiler::
      000008                         38 	.ds 3
      00000B                         39 _info_platform::
      00000B                         40 	.ds 3
      00000E                         41 _info_arch::
      00000E                         42 	.ds 3
      000011                         43 _info_language_dialect_default::
      000011                         44 	.ds 3
                                     45 ;--------------------------------------------------------
                                     46 ; overlayable items in internal ram 
                                     47 ;--------------------------------------------------------
                                     48 	.area	OSEG    (OVR,DATA)
      000014                         49 _main_PARM_2:
      000014                         50 	.ds 3
                                     51 ;--------------------------------------------------------
                                     52 ; Stack segment in internal ram 
                                     53 ;--------------------------------------------------------
                                     54 	.area	SSEG
      000017                         55 __start__stack:
      000017                         56 	.ds	1
                                     57 
                                     58 ;--------------------------------------------------------
                                     59 ; indirectly addressable internal ram data
                                     60 ;--------------------------------------------------------
                                     61 	.area ISEG    (DATA)
                                     62 ;--------------------------------------------------------
                                     63 ; absolute internal ram data
                                     64 ;--------------------------------------------------------
                                     65 	.area IABS    (ABS,DATA)
                                     66 	.area IABS    (ABS,DATA)
                                     67 ;--------------------------------------------------------
                                     68 ; bit data
                                     69 ;--------------------------------------------------------
                                     70 	.area BSEG    (BIT)
                                     71 ;--------------------------------------------------------
                                     72 ; paged external ram data
                                     73 ;--------------------------------------------------------
                                     74 	.area PSEG    (PAG,XDATA)
                                     75 ;--------------------------------------------------------
                                     76 ; external ram data
                                     77 ;--------------------------------------------------------
                                     78 	.area XSEG    (XDATA)
                                     79 ;--------------------------------------------------------
                                     80 ; absolute external ram data
                                     81 ;--------------------------------------------------------
                                     82 	.area XABS    (ABS,XDATA)
                                     83 ;--------------------------------------------------------
                                     84 ; external initialized ram data
                                     85 ;--------------------------------------------------------
                                     86 	.area XISEG   (XDATA)
                                     87 	.area HOME    (CODE)
                                     88 	.area GSINIT0 (CODE)
                                     89 	.area GSINIT1 (CODE)
                                     90 	.area GSINIT2 (CODE)
                                     91 	.area GSINIT3 (CODE)
                                     92 	.area GSINIT4 (CODE)
                                     93 	.area GSINIT5 (CODE)
                                     94 	.area GSINIT  (CODE)
                                     95 	.area GSFINAL (CODE)
                                     96 	.area CSEG    (CODE)
                                     97 ;--------------------------------------------------------
                                     98 ; interrupt vector 
                                     99 ;--------------------------------------------------------
                                    100 	.area HOME    (CODE)
      000000                        101 __interrupt_vect:
      000000 02 00 06         [24]  102 	ljmp	__sdcc_gsinit_startup
                                    103 ;--------------------------------------------------------
                                    104 ; global & static initialisations
                                    105 ;--------------------------------------------------------
                                    106 	.area HOME    (CODE)
                                    107 	.area GSINIT  (CODE)
                                    108 	.area GSFINAL (CODE)
                                    109 	.area GSINIT  (CODE)
                                    110 	.globl __sdcc_gsinit_startup
                                    111 	.globl __sdcc_program_startup
                                    112 	.globl __start__stack
                                    113 	.globl __mcs51_genXINIT
                                    114 	.globl __mcs51_genXRAMCLEAR
                                    115 	.globl __mcs51_genRAMCLEAR
                                    116 ;	CMakeCCompilerId.c:289: char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
      00005F 75 08 57         [24]  117 	mov	_info_compiler,#___str_0
      000062 75 09 01         [24]  118 	mov	(_info_compiler + 1),#(___str_0 >> 8)
      000065 75 0A 80         [24]  119 	mov	(_info_compiler + 2),#0x80
                                    120 ;	CMakeCCompilerId.c:514: char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
      000068 75 0B 6B         [24]  121 	mov	_info_platform,#___str_1
      00006B 75 0C 01         [24]  122 	mov	(_info_platform + 1),#(___str_1 >> 8)
      00006E 75 0D 80         [24]  123 	mov	(_info_platform + 2),#0x80
                                    124 ;	CMakeCCompilerId.c:515: char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";
      000071 75 0E 7B         [24]  125 	mov	_info_arch,#___str_2
      000074 75 0F 01         [24]  126 	mov	(_info_arch + 1),#(___str_2 >> 8)
      000077 75 10 80         [24]  127 	mov	(_info_arch + 2),#0x80
                                    128 ;	CMakeCCompilerId.c:533: const char* info_language_dialect_default =
      00007A 75 11 87         [24]  129 	mov	_info_language_dialect_default,#___str_3
      00007D 75 12 01         [24]  130 	mov	(_info_language_dialect_default + 1),#(___str_3 >> 8)
      000080 75 13 80         [24]  131 	mov	(_info_language_dialect_default + 2),#0x80
                                    132 	.area GSFINAL (CODE)
      000083 02 00 03         [24]  133 	ljmp	__sdcc_program_startup
                                    134 ;--------------------------------------------------------
                                    135 ; Home
                                    136 ;--------------------------------------------------------
                                    137 	.area HOME    (CODE)
                                    138 	.area HOME    (CODE)
      000003                        139 __sdcc_program_startup:
      000003 02 00 86         [24]  140 	ljmp	_main
                                    141 ;	return from main will return to caller
                                    142 ;--------------------------------------------------------
                                    143 ; code
                                    144 ;--------------------------------------------------------
                                    145 	.area CSEG    (CODE)
                                    146 ;------------------------------------------------------------
                                    147 ;Allocation info for local variables in function 'main'
                                    148 ;------------------------------------------------------------
                                    149 ;argv                      Allocated with name '_main_PARM_2'
                                    150 ;argc                      Allocated to registers r6 r7 
                                    151 ;require                   Allocated to registers r3 r5 
                                    152 ;------------------------------------------------------------
                                    153 ;	CMakeCCompilerId.c:544: int main(int argc, char* argv[])
                                    154 ;	-----------------------------------------
                                    155 ;	 function main
                                    156 ;	-----------------------------------------
      000086                        157 _main:
                           000007   158 	ar7 = 0x07
                           000006   159 	ar6 = 0x06
                           000005   160 	ar5 = 0x05
                           000004   161 	ar4 = 0x04
                           000003   162 	ar3 = 0x03
                           000002   163 	ar2 = 0x02
                           000001   164 	ar1 = 0x01
                           000000   165 	ar0 = 0x00
      000086 AE 82            [24]  166 	mov	r6,dpl
      000088 AF 83            [24]  167 	mov	r7,dph
                                    168 ;	CMakeCCompilerId.c:548: require += info_compiler[argc];
      00008A EE               [12]  169 	mov	a,r6
      00008B 25 08            [12]  170 	add	a,_info_compiler
      00008D FB               [12]  171 	mov	r3,a
      00008E EF               [12]  172 	mov	a,r7
      00008F 35 09            [12]  173 	addc	a,(_info_compiler + 1)
      000091 FC               [12]  174 	mov	r4,a
      000092 AD 0A            [24]  175 	mov	r5,(_info_compiler + 2)
      000094 8B 82            [24]  176 	mov	dpl,r3
      000096 8C 83            [24]  177 	mov	dph,r4
      000098 8D F0            [24]  178 	mov	b,r5
      00009A 12 01 05         [24]  179 	lcall	__gptrget
      00009D FB               [12]  180 	mov	r3,a
      00009E 7D 00            [12]  181 	mov	r5,#0x00
                                    182 ;	CMakeCCompilerId.c:549: require += info_platform[argc];
      0000A0 EE               [12]  183 	mov	a,r6
      0000A1 25 0B            [12]  184 	add	a,_info_platform
      0000A3 F9               [12]  185 	mov	r1,a
      0000A4 EF               [12]  186 	mov	a,r7
      0000A5 35 0C            [12]  187 	addc	a,(_info_platform + 1)
      0000A7 FA               [12]  188 	mov	r2,a
      0000A8 AC 0D            [24]  189 	mov	r4,(_info_platform + 2)
      0000AA 89 82            [24]  190 	mov	dpl,r1
      0000AC 8A 83            [24]  191 	mov	dph,r2
      0000AE 8C F0            [24]  192 	mov	b,r4
      0000B0 12 01 05         [24]  193 	lcall	__gptrget
      0000B3 7C 00            [12]  194 	mov	r4,#0x00
      0000B5 2B               [12]  195 	add	a,r3
      0000B6 FB               [12]  196 	mov	r3,a
      0000B7 EC               [12]  197 	mov	a,r4
      0000B8 3D               [12]  198 	addc	a,r5
      0000B9 FD               [12]  199 	mov	r5,a
                                    200 ;	CMakeCCompilerId.c:550: require += info_arch[argc];
      0000BA EE               [12]  201 	mov	a,r6
      0000BB 25 0E            [12]  202 	add	a,_info_arch
      0000BD F9               [12]  203 	mov	r1,a
      0000BE EF               [12]  204 	mov	a,r7
      0000BF 35 0F            [12]  205 	addc	a,(_info_arch + 1)
      0000C1 FA               [12]  206 	mov	r2,a
      0000C2 AC 10            [24]  207 	mov	r4,(_info_arch + 2)
      0000C4 89 82            [24]  208 	mov	dpl,r1
      0000C6 8A 83            [24]  209 	mov	dph,r2
      0000C8 8C F0            [24]  210 	mov	b,r4
      0000CA 12 01 05         [24]  211 	lcall	__gptrget
      0000CD 7C 00            [12]  212 	mov	r4,#0x00
      0000CF 2B               [12]  213 	add	a,r3
      0000D0 FB               [12]  214 	mov	r3,a
      0000D1 EC               [12]  215 	mov	a,r4
      0000D2 3D               [12]  216 	addc	a,r5
      0000D3 FD               [12]  217 	mov	r5,a
                                    218 ;	CMakeCCompilerId.c:552: require += info_version[argc];
      0000D4 EE               [12]  219 	mov	a,r6
      0000D5 24 25            [12]  220 	add	a,#_info_version
      0000D7 F5 82            [12]  221 	mov	dpl,a
      0000D9 EF               [12]  222 	mov	a,r7
      0000DA 34 01            [12]  223 	addc	a,#(_info_version >> 8)
      0000DC F5 83            [12]  224 	mov	dph,a
      0000DE E4               [12]  225 	clr	a
      0000DF 93               [24]  226 	movc	a,@a+dptr
      0000E0 7A 00            [12]  227 	mov	r2,#0x00
      0000E2 2B               [12]  228 	add	a,r3
      0000E3 FB               [12]  229 	mov	r3,a
      0000E4 EA               [12]  230 	mov	a,r2
      0000E5 3D               [12]  231 	addc	a,r5
      0000E6 FD               [12]  232 	mov	r5,a
                                    233 ;	CMakeCCompilerId.c:563: require += info_language_dialect_default[argc];
      0000E7 EE               [12]  234 	mov	a,r6
      0000E8 25 11            [12]  235 	add	a,_info_language_dialect_default
      0000EA FE               [12]  236 	mov	r6,a
      0000EB EF               [12]  237 	mov	a,r7
      0000EC 35 12            [12]  238 	addc	a,(_info_language_dialect_default + 1)
      0000EE FF               [12]  239 	mov	r7,a
      0000EF AC 13            [24]  240 	mov	r4,(_info_language_dialect_default + 2)
      0000F1 8E 82            [24]  241 	mov	dpl,r6
      0000F3 8F 83            [24]  242 	mov	dph,r7
      0000F5 8C F0            [24]  243 	mov	b,r4
      0000F7 12 01 05         [24]  244 	lcall	__gptrget
      0000FA 7F 00            [12]  245 	mov	r7,#0x00
      0000FC 2B               [12]  246 	add	a,r3
      0000FD FB               [12]  247 	mov	r3,a
      0000FE EF               [12]  248 	mov	a,r7
      0000FF 3D               [12]  249 	addc	a,r5
                                    250 ;	CMakeCCompilerId.c:565: return require;
      000100 8B 82            [24]  251 	mov	dpl,r3
      000102 F5 83            [12]  252 	mov	dph,a
      000104 22               [24]  253 	ret
                                    254 	.area CSEG    (CODE)
                                    255 	.area CONST   (CODE)
      000125                        256 _info_version:
      000125 49                     257 	.db #0x49	; 73	'I'
      000126 4E                     258 	.db #0x4e	; 78	'N'
      000127 46                     259 	.db #0x46	; 70	'F'
      000128 4F                     260 	.db #0x4f	; 79	'O'
      000129 3A                     261 	.db #0x3a	; 58
      00012A 63                     262 	.db #0x63	; 99	'c'
      00012B 6F                     263 	.db #0x6f	; 111	'o'
      00012C 6D                     264 	.db #0x6d	; 109	'm'
      00012D 70                     265 	.db #0x70	; 112	'p'
      00012E 69                     266 	.db #0x69	; 105	'i'
      00012F 6C                     267 	.db #0x6c	; 108	'l'
      000130 65                     268 	.db #0x65	; 101	'e'
      000131 72                     269 	.db #0x72	; 114	'r'
      000132 5F                     270 	.db #0x5f	; 95
      000133 76                     271 	.db #0x76	; 118	'v'
      000134 65                     272 	.db #0x65	; 101	'e'
      000135 72                     273 	.db #0x72	; 114	'r'
      000136 73                     274 	.db #0x73	; 115	's'
      000137 69                     275 	.db #0x69	; 105	'i'
      000138 6F                     276 	.db #0x6f	; 111	'o'
      000139 6E                     277 	.db #0x6e	; 110	'n'
      00013A 5B                     278 	.db #0x5b	; 91
      00013B 30                     279 	.db #0x30	; 48	'0'
      00013C 30                     280 	.db #0x30	; 48	'0'
      00013D 30                     281 	.db #0x30	; 48	'0'
      00013E 30                     282 	.db #0x30	; 48	'0'
      00013F 30                     283 	.db #0x30	; 48	'0'
      000140 30                     284 	.db #0x30	; 48	'0'
      000141 30                     285 	.db #0x30	; 48	'0'
      000142 33                     286 	.db #0x33	; 51	'3'
      000143 2E                     287 	.db #0x2e	; 46
      000144 30                     288 	.db #0x30	; 48	'0'
      000145 30                     289 	.db #0x30	; 48	'0'
      000146 30                     290 	.db #0x30	; 48	'0'
      000147 30                     291 	.db #0x30	; 48	'0'
      000148 30                     292 	.db #0x30	; 48	'0'
      000149 30                     293 	.db #0x30	; 48	'0'
      00014A 30                     294 	.db #0x30	; 48	'0'
      00014B 36                     295 	.db #0x36	; 54	'6'
      00014C 2E                     296 	.db #0x2e	; 46
      00014D 30                     297 	.db #0x30	; 48	'0'
      00014E 30                     298 	.db #0x30	; 48	'0'
      00014F 30                     299 	.db #0x30	; 48	'0'
      000150 30                     300 	.db #0x30	; 48	'0'
      000151 30                     301 	.db #0x30	; 48	'0'
      000152 30                     302 	.db #0x30	; 48	'0'
      000153 30                     303 	.db #0x30	; 48	'0'
      000154 30                     304 	.db #0x30	; 48	'0'
      000155 5D                     305 	.db #0x5d	; 93
      000156 00                     306 	.db #0x00	; 0
      000157                        307 ___str_0:
      000157 49 4E 46 4F 3A 63 6F   308 	.ascii "INFO:compiler[SDCC]"
             6D 70 69 6C 65 72 5B
             53 44 43 43 5D
      00016A 00                     309 	.db 0x00
      00016B                        310 ___str_1:
      00016B 49 4E 46 4F 3A 70 6C   311 	.ascii "INFO:platform[]"
             61 74 66 6F 72 6D 5B
             5D
      00017A 00                     312 	.db 0x00
      00017B                        313 ___str_2:
      00017B 49 4E 46 4F 3A 61 72   314 	.ascii "INFO:arch[]"
             63 68 5B 5D
      000186 00                     315 	.db 0x00
      000187                        316 ___str_3:
      000187 49 4E 46 4F 3A 64 69   317 	.ascii "INFO:dialect_default[11]"
             61 6C 65 63 74 5F 64
             65 66 61 75 6C 74 5B
             31 31 5D
      00019F 00                     318 	.db 0x00
                                    319 	.area XINIT   (CODE)
                                    320 	.area CABS    (ABS,CODE)
