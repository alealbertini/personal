global bandas_asm

section .data
section .rodata

; PROCESAMOS DE A 4 PIXELES
ALIGN 16
colores0: 				DW  0x0, 0x0,  0x0, 0x0,				; 0, 0, 0, 0
						DW  0x0, 0x0,  0x0, 0x0,				; 0, 0, 0, 0
ALIGN 16	
colores1: 				DB  0x40, 0x40, 0x40, 0x00,				; 64, 64, 64, 0
						DB  0x40, 0x40, 0x40, 0x00,				; 64, 64, 64, 0
						DB  0x40, 0x40, 0x40, 0x00,				; 64, 64, 64, 0
						DB  0x40, 0x40, 0x40, 0x00,				; 64, 64, 64, 0

ALIGN 16	
colores2: 				DB  0x80, 0x80, 0x80, 0x00,				; 128, 128, 128, 0
						DB  0x80, 0x80, 0x80, 0x00,				; 128, 128, 128, 0
						DB  0x80, 0x80, 0x80, 0x00,				; 128, 128, 128, 0
						DB  0x80, 0x80, 0x80, 0x00,				; 128, 128, 128, 0
ALIGN 16	
colores3: 				DB 	0xC0, 0xC0, 0xC0, 0x00,				; 192, 192, 192, 0
						DB 	0xC0, 0xC0, 0xC0, 0x00,				; 192, 192, 192, 0
						DB 	0xC0, 0xC0, 0xC0, 0x00,				; 192, 192, 192, 0
						DB 	0xC0, 0xC0, 0xC0, 0x00,				; 192, 192, 192, 0
ALIGN 16	
colores4: 				DB  0xFF, 0xFF, 0xFF, 0x00,				; 255, 255, 255, 0
						DB  0xFF, 0xFF, 0xFF, 0x00,				; 255, 255, 255, 0
						DB  0xFF, 0xFF, 0xFF, 0x00,				; 255, 255, 255, 0
						DB  0xFF, 0xFF, 0xFF, 0x00,				; 255, 255, 255, 0
ALIGN 16 
nueveCinco: 			DD 0x5F, 0x5F, 0x5F, 0x5F				; 95, 95, 95, 95			
ALIGN 16 
seisSieteUno: 			DD 0x29F, 0x29F, 0x29F, 0x29F			; 671, 671, 671, 671 	
ALIGN 16 
cuatroSieteNueve: 		DD 0x1DF, 0x1DF, 0x1DF, 0x1DF			; 479, 479, 479, 479	
ALIGN 16 
dosOchoSiete:			DD 0x11F, 0x11F, 0x11F, 0x11F			; 287, 287, 287, 287

; MASCARAS
ALIGN 16
aPorCero : 				DB  0x00, 0x01, 0x02, 0x80, ; [ R , G , B , 0
						DB  0x04, 0x05, 0x06, 0x80, ;   R , G , B , 0
						DB  0x08, 0x09, 0x0A, 0x80, ;   R , G , B , 0
						DB  0x0C, 0x0D, 0x0E, 0x80  ;   R , G , B , 0 ]

ALIGN 16
soloA:					DB  0x80, 0x80, 0x80, 0x03, ; [ R , G , B , 0
						DB  0x80, 0x80, 0x80, 0x07, ;   R , G , B , 0
						DB  0x80, 0x80, 0x80, 0x0B, ;   R , G , B , 0
						DB  0x80, 0x80, 0x80, 0x0F  ;   R , G , B , 0 ]

ALIGN 16
soloPrimero : 			DB  0x00, 0x80, 0x80, 0x80, ; [ 1 , - , - , -
						DB  0x04, 0x80, 0x80, 0x80, ;   2 , - , - , -
						DB  0x08, 0x80, 0x80, 0x80, ;   3 , - , - , -
						DB  0x0C, 0x80, 0x80, 0x80  ;   4 , - , - , - ]


section .text


bandas_asm:
		;RDI: unsigned char *src,
		;RSI: unsigned char *dst,
		;RDX: int cols,
		;RCX: int filas,
		;R8: int src_row_size,
		;R9: int dst_row_size

		;unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
		;unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;

		;for (int i = 0; i < filas; i++) 
		;{
		;	for (int j = 0; j < cols; j++) 
		;	{
		;		bgr_t *p_d = (bgr_t*)&dst_matrix[i][j*4];
		;		bgr_t *p_s = (bgr_t*)&src_matrix[i][j*4];
		;		bandas(p_d, p_s->b, p_s->g, p_s->r);
		;	}
		;}
		PUSH RBP					
		MOV RBP, RSP
		PUSH R12
		PUSH R13
		PUSH R14
		PUSH R15
		PUSH RDX
		SUB RSP, 8

		MOV R12, RDI
		MOV R13, RSI
		MOV R14, RCX
		MOV R15, RDX
		XOR R8, R8
		DEC R8
	.for1:
		;for (int i = 0; i < filas; i++) {
		INC R8
		CMP R8, R14
		JGE .fin
		XOR R9, R9
	.for2:
			;for (int j = 0; j < cols; j++) {
			CMP R9, R15
			JGE .for1
				;bgr_t *p_d = (bgr_t*)&dst_matrix[i][j*4];
				;bgr_t *p_s = (bgr_t*)&src_matrix[i][j*4];
				MOVDQU XMM0, [R12]
				;bandas(p_d, p_s->b, p_s->g, p_s->r);}}
				PUSH R8
				PUSH R9
				SUB RSP, 8
				CALL bandas
				ADD RSP, 8
				POP R9
				POP R8
				MOVDQU [R13], XMM0
				LEA R12, [R12+16]
				LEA R13, [R13+16]
				;ADD R12, 4
				;ADD R13, 4
				ADD R9, 4
				JMP .for2
	.fin:
	 	ADD RSP, 8
	 	POP RDX
	 	POP R15
	 	POP R14
	 	POP R13
	 	POP R12
	 	POP RBP
		RET

bandas:
;void bandas(bgr_t* p_d, unsigned int r, unsigned int g, unsigned int b){
	;unsigned int suma = (r + g + b);
	;if 	(suma < 96)		{p_d->b = 0; 	p_d->g = 0; 	p_d->r = 0;}		colores0
	;else if (suma < 288)	{p_d->b = 64; 	p_d->g = 64; 	p_d->r = 64;}		colores1
	;else if (suma < 480)	{p_d->b = 128;	p_d->g = 128; 	p_d->r = 128;}		colores2
	;else if (suma < 672)	{p_d->b = 192; 	p_d->g = 192;	p_d->r = 192;}		colores3
	;else 					{p_d->b = 255;	p_d->g = 255; 	p_d->r = 255;}}		colores4

	;//ME TENGO QUE ASEGURAR DE PRESERVAR LOS REGISTROS: 
	;//YA SE QUE NO RESPETO LA CONVENCION C, PERO COMO ES MI CODIGO Y SE LO QUE ESTOY HACIENDO, NO PASA NADA
	;XMM0: p_s
	
		PUSH RBP
		MOV RBP, RSP
	
		;GUARDO EL VALOR 'A' DE CADA PIXEL PARA RESTAURARLO DESPUES
		MOVDQU XMM5, XMM0
		PSHUFB XMM5, [soloA]

		;CALCULO 'suma'
		;XMM0: R1 | G1 | B1 | A1 || R2 | G2 | B2 | A2 || R3 | G3 | B3 | A3 || R4 | G4 | B4 | A4
		MOVDQU XMM1, XMM0					; XMM1: R|G|B|A|R|G|B|A|R|G|B|A|R|G|B|A
		PSHUFB XMM1, [soloPrimero]			; XMM1: R|0|0|0|R|0|0|0|R|0|0|0|R|0|0|0		; solo dejamos rojo para 'suma'
		MOVDQU XMM3, XMM0					; XMM3: R|G|B|A|R|G|B|A|R|G|B|A|R|G|B|A
		PSRLD XMM3, 8						; XMM3: G|B|A|R|G|B|A|R|G|B|A|R|G|B|A|0
		PSHUFB XMM3, [soloPrimero]			; XMM3: G|0|0|0|G|0|0|0|G|0|0|0|G|0|0|0		; solo dejamos verde para 'suma'
		MOVDQU XMM4, XMM0					; XMM4: R|G|B|A|R|G|B|A|R|G|B|A|R|G|B|A
		PSRLD XMM4, 16						; XMM4: B|A|R|G|B|A|R|G|B|A|R|G|B|A|0|0		; solo dejamos azul para 'suma'
		PSHUFB XMM4, [soloPrimero]			; XMM4: B|0|0|0|B|0|0|0|B|0|0|0|B|0|0|0		; solo dejamos azul para 'suma'
		; Ahora podemos hacer suma
		PADDW XMM1, XMM3
		PADDW XMM1, XMM4					; XMM1: dword[R+G+B] dword[R+G+B] dword[R+G+B] dword[R+G+B] 
		;XMM1: suma

		MOVDQU XMM10, [colores0] 	

		MOVDQU XMM0, XMM10
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		MOVDQU XMM10, [colores4]

		MOVDQU XMM2, [seisSieteUno] 
		PCMPGTD XMM2, XMM1				; en XMM2 tenemos unos donde se cumple la condicion

		MOVDQU XMM3, [seisSieteUno] 
		PCMPEQD XMM3, XMM1 				; en XMM3 tenemos unos donde son iguales
		POR XMM2, XMM3

		PAND XMM1, XMM2					; seteo en 0 los que ya use para no pisarlos despues
		PANDN XMM2 , XMM10 				; estos pixeles le ponemos colores[4]
		POR XMM0, XMM2					; ponemos colores4 en donde va en dst
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		MOVDQU XMM10 , [colores3]

		MOVDQU XMM2, [cuatroSieteNueve] 
		PCMPGTD XMM2, XMM1			; en XMM2 tenemos unos donde se cumple la condicion

		MOVDQU XMM3, [cuatroSieteNueve] 
		PCMPEQD XMM3, XMM1 			; en XMM3 tenemos unos donde son iguales
		POR XMM2, XMM3

		PAND XMM1, XMM2 			; seteo en 0 los que ya use para no pisarlos despues
		PANDN XMM2 , XMM10 			; estos pixeles le ponemos colores[3]
		POR XMM0, XMM2				; ponemos colores3 en donde va en dst
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		MOVDQU XMM10 ,[colores2] 	

		MOVDQU XMM2, [dosOchoSiete] 
		PCMPGTD XMM2, XMM1			; en XMM2 tenemos unos donde se cumple la condicion

		MOVDQU XMM3, [dosOchoSiete] 
		PCMPEQD XMM3, XMM1 			; en XMM3 tenemos unos donde son iguales
		POR XMM2, XMM3

		PAND XMM1, XMM2 			; seteo en 0 los que ya use para no pisarlos despues
		PANDN XMM2, XMM10 			; estos pixeles le ponemos colores[2]
		POR XMM0, XMM2				; ponemos colores2 en donde va en dst
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		MOVDQU XMM10 ,[colores1] 	

		MOVDQU XMM2, [nueveCinco] 
		PCMPGTD XMM2, XMM1			; en XMM2 tenemos unos donde se cumple la condicion

		MOVDQU XMM3, [nueveCinco] 
		PCMPEQD XMM3, XMM1 			; en XMM3 tenemos unos donde son iguales
		POR XMM2, XMM3

		PAND XMM1, XMM2 			; seteo en 0 los que ya use para no pisarlos despues
		PANDN XMM2, XMM10 			; estos pixeles le ponemos colores[1]
		POR XMM0, XMM2				; ponemos colores1 en donde va en dst
		;///////////////////////////////////////////////////////////////////////////////////////////////////
		;///////////////////////////////////////////////////////////////////////////////////////////////////	

		;RESTAURO 'A' DE CADA PIXEL
		PADDB XMM0, XMM5
		
		POP RBP
		RET