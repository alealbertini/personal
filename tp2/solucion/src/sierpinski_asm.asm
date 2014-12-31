global sierpinski_asm

section .data
valor: dq 255.0
section .text

;void sierpinski_asm (unsigned char *src,
;                     unsigned char *dst,
;                     int cols, int rows,
;                     int src_row_size,
;                     int dst_row_size)

sierpinski_asm:
	; RDI = UNSIGNED CHAR *SRC
	; RSI = UNSIGNED CHAR *DST
	; RDX = INT COLS
	; RCX = INT ROWS
	; R8 = INT SRC_ROW_SIZE
	; R9 = INT DST_ROW_SIZE
	
	push RBP					
	mov RBP, RSP
	push RBX
	push R12
	push R13
	push R14
	push R15
	sub RSP, 8
	
	mov R12, RDI ; R12 = UNSIGNED CHAR *SRC
	mov R13, RSI ; R13 = UNSIGNED CHAR *DST	
	
	xor R10, R10
	.cicloFilas:
		cmp R10D, ECX
		je .finCicloFilas
		xor R11, R11
		.cicloColumnas:
			cmp R11D, EDX
			je .finCicloColumnas
			
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
	;		add rax, rbx
			
			xor R14, R14
			xor R15, R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			cvtsi2sd XMM0, R11 ; XMM0 = COLUMNA ACTUAL
			cvtsi2sd XMM1, R10 ; XMM1 = FILA ACTUAL
			mulsd XMM0, [valor] ; XMM0 = COLUMNA ACTUAL * 255.0
			mulsd XMM1, [valor] ; XMM1 = FILA ACTUAL * 255.0
			cvtsi2sd XMM2, RDX ; XMM2 = COLUMNAS TOTALES
			cvtsi2sd XMM3, RCX ; XMM3 = FILAS TOTALES
			divsd XMM0, XMM2 ; XMM0 = (I*255.5)/COLUMNAS
			divsd XMM1, XMM3 ; XMM1 =  (J*255.5)/FILAS
			cvttsd2si R14, XMM0 ; R14 = (INT) (I*255.5)/COLUMNAS
			cvttsd2si R15, XMM1 ; R15 = (INT) (J*255.5)/FILAS
			xor R14, R15 ; R14 = R14 XOR R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			xor R15, R15
			mov R15, 1
			;movq XMM0, R15
			cvtsi2sd XMM0, R15
			divsd XMM0, [valor] ; XMM0 = 1/255.0
			cvtsi2sd XMM1, R14
			mulsd XMM0, XMM1 ; XMM0 = COEF
			movdqu XMM2, XMM0 ; XMM2 = COEF
			pslldq XMM0, 8
			addsd XMM0, XMM2 ; XMM00 = [COEF | COEF]
			
			xorpd XMM2, XMM2		
			movdqu XMM1, [R12] ;XMM1 = { [B|G|R|A][B|G|R|A][B|G|R|A][B|G|R|A] }
			punpcklbw XMM1, XMM2 ; XMM1 = { [0|B|0|G][0|R|0|A][0|B|0|G][0|R|0|A] }
			punpcklwd XMM1, XMM2 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			movdqu XMM3, XMM1 ; XMM3 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			psrldq XMM3, 8 ; XMM3 = { [0|0|0|R][0|0|0|A][0|0|0|0][0|0|0|0] }
			cvtdq2pd XMM1, XMM1 ; XMM1 = { [B|0|0|0][0|0|0|0][0|0|0|0][0|0|0|G] } DOUBLE
			cvtdq2pd XMM3, XMM3 ; XMM3 = { [R|0|0|0][0|0|0|0][0|0|0|0][0|0|0|A] } DOUBLE

			mulpd XMM1, XMM0 ; XMM1 = { [0|0|0|0][0|0|0|B][0|0|0|0][0|0|0|G] } * COEF
			mulpd XMM3, XMM0 ; XMM3 = { [0|0|0|0][0|0|0|R][0|0|0|0][0|0|0|A] } * COEF


			cvttpd2dq XMM1, XMM1 ; XMM1 = { [B|0|0|0][G|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			cvttpd2dq XMM3, XMM3 ; XMM3 = { [R|0|0|0][A|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			pslldq XMM3, 8 ; XMM1 = { [0|0|0|0][0|0|0|0][R|0|0|0][A|0|0|0] }
			paddd XMM1, XMM3 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			
			xorpd XMM3, XMM3 ; XMM3 = { [0] }
			
			packusdw XMM1, XMM3 ; XMM1 = { [B|0|G|0][R|0|A|0][0|0|0|0][0|0|0|0] }   ; ESTO ES ILLEGAL!
			packuswb XMM1, XMM3 ; XMM1 = { [B|G|R|A][0|0|0|0][0|0|0|0][0|0|0|0] }
			
			xorpd XMM4, XMM4
			movdqu XMM4, XMM1 ; XMM4 = { [B|G|R|A][0|0|0|0][0|0|0|0][0|0|0|0] }
			;pslldq XMM4, 12 ; XMM4 = { [B|G|R|A][0|0|0|0][0|0|0|0][0|0|0|0] }
			inc R11
			;-----------------------------------------------------------------------------------------
			xor R14, R14
			xor R15, R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			cvtsi2sd XMM0, R11 ; XMM0 = COLUMNA ACTUAL
			cvtsi2sd XMM1, R10 ; XMM1 = FILA ACTUAL
			mulsd XMM0, [valor] ; XMM0 = COLUMNA ACTUAL * 255.5
			mulsd XMM1, [valor] ; XMM1 = FILA ACTUAL * 255.5
			cvtsi2sd XMM2, RDX ; XMM2 = COLUMNAS TOTALES
			cvtsi2sd XMM3, RCX ; XMM3 = FILAS TOTALES
			divsd XMM0, XMM2 ; XMM0 = (I*255.5)/COLUMNAS
			divsd XMM1, XMM3 ; XMM1 =  (J*255.5)/FILAS
			cvttsd2si R14, XMM0 ; R14 = (INT) (I*255.5)/COLUMNAS
			cvttsd2si R15, XMM1 ; R15 = (INT) (J*255.5)/FILAS
			xor R14, R15 ; R14 = R14 XOR R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			xor R15, R15
			mov R15, 1
			;movq XMM0, R15
			cvtsi2sd XMM0, R15
			divsd XMM0, [valor] ; XMM0 = 1/255.0
			cvtsi2sd XMM1, R14
			mulsd XMM0, XMM1 ; XMM0 = COEF
			movdqu XMM2, XMM0 ; XMM2 = COEF
			pslldq XMM0, 8
			addsd XMM0, XMM2
			
			xorpd XMM2, XMM2		
			movdqu XMM1, [R12] ;XMM1 = { [B|G|R|A][B|G|R|A][B|G|R|A][B|G|R|A] }
			psrldq XMM1, 4 ;XMM1 = { [B|G|R|A][B|G|R|A][B|G|R|A][0|0|0|0] }
			xorpd XMM2, XMM2		
			punpcklbw XMM1, XMM2 ; XMM1 = { [0|B|0|G][0|R|0|A][0|B|0|G][0|R|0|A] }
			punpcklwd XMM1, XMM2 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			movdqu XMM3, XMM1 ; XMM3 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			psrldq XMM3, 8 ; XMM3 = { [0|0|0|R][0|0|0|A][0|0|0|0][0|0|0|0] }
			cvtdq2pd XMM1, XMM1 ; XMM1 = { [B|0|0|0][0|0|0|0][0|0|0|0][0|0|0|G] } DOUBLE
			cvtdq2pd XMM3, XMM3 ; XMM3 = { [R|0|0|0][0|0|0|0][0|0|0|0][0|0|0|A] } DOUBLE
			mulpd XMM1, XMM0 ; XMM1 = { [0|0|0|0][0|0|0|B][0|0|0|0][0|0|0|G] } * COEF
			mulpd XMM3, XMM0 ; XMM3 = { [0|0|0|0][0|0|0|R][0|0|0|0][0|0|0|A] } * COEF
			cvttpd2dq XMM1, XMM1 ; XMM1 = { [B|0|0|0][G|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			cvttpd2dq XMM3, XMM3 ; XMM3 = { [R|0|0|0][A|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			pslldq XMM3, 8 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|0][0|0|0|0] }
			paddd XMM1, XMM3 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }		
			xorpd XMM3, XMM3 ; XMM3 = { [0] }		
			packusdw XMM1, XMM3 ; XMM1 = { [0|0|0|0][0|0|0|0][0|B|0|G][0|R|0|A] }   ; ESTO ES ILLEGAL!
			packuswb XMM1, XMM3 ; XMM1 = { [0|0|0|0][0|0|0|0][0|0|0|0][B|G|R|A] }

			pslldq XMM1, 4  ; XMM1 = { [0|0|0|0][B|G|R|A][0|0|0|0][0|0|0|0] }
			paddusb XMM4, XMM1 ; XMM4 = { [B|G|R|A][B|G|R|A][0|0|0|0][0|0|0|0] } 
			inc R11
			;-----------------------------------------------------------------------------------------
			xor R14, R14
			xor R15, R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			cvtsi2sd XMM0, R11 ; XMM0 = COLUMNA ACTUAL
			cvtsi2sd XMM1, R10 ; XMM1 = FILA ACTUAL
			mulsd XMM0, [valor] ; XMM0 = COLUMNA ACTUAL * 255.5
			mulsd XMM1, [valor] ; XMM1 = FILA ACTUAL * 255.5
			cvtsi2sd XMM2, RDX ; XMM2 = COLUMNAS TOTALES
			cvtsi2sd XMM3, RCX ; XMM3 = FILAS TOTALES
			divsd XMM0, XMM2 ; XMM0 = (I*255.5)/COLUMNAS
			divsd XMM1, XMM3 ; XMM1 =  (J*255.5)/FILAS
			cvttsd2si R14, XMM0 ; R14 = (INT) (I*255.5)/COLUMNAS
			cvttsd2si R15, XMM1 ; R15 = (INT) (J*255.5)/FILAS
			xor R14, R15 ; R14 = R14 XOR R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			xor R15, R15
			mov R15, 1
			;movq XMM0, R15
			cvtsi2sd XMM0, R15
			divsd XMM0, [valor] ; XMM0 = 1/255.0
			cvtsi2sd XMM1, R14
			mulsd XMM0, XMM1 ; XMM0 = COEF
			movdqu XMM2, XMM0 ; XMM2 = COEF
			pslldq XMM0, 8
			addsd XMM0, XMM2
			
			xorpd XMM2, XMM2		
			movdqu XMM1, [R12] ; XMM1 = { [R|G|B|A][R|G|B|A][R|G|B|A][R|G|B|A] }
			psrldq XMM1, 8 ; XMM1 = { [R|G|B|A][R|G|B|A][0|0|0|0][0|0|0|0] } 
			xorpd XMM2, XMM2		
			punpcklbw XMM1, XMM2 ; XMM1 = { [0|B|0|G][0|R|0|A][0|B|0|G][0|R|0|A] }
			punpcklwd XMM1, XMM2 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			movdqu XMM3, XMM1 ; XMM3 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			psrldq XMM3, 8 ; XMM3 = { [0|0|0|R][0|0|0|A][0|0|0|0][0|0|0|0] }
			cvtdq2pd XMM1, XMM1 ; XMM1 = { [B|0|0|0][0|0|0|0][0|0|0|0][0|0|0|G] } DOUBLE
			cvtdq2pd XMM3, XMM3 ; XMM3 = { [R|0|0|0][0|0|0|0][0|0|0|0][0|0|0|A] } DOUBLE
			mulpd XMM1, XMM0 ; XMM1 = { [0|0|0|0][0|0|0|B][0|0|0|0][0|0|0|G] } * COEF
			mulpd XMM3, XMM0 ; XMM3 = { [0|0|0|0][0|0|0|R][0|0|0|0][0|0|0|A] } * COEF
			cvttpd2dq XMM1, XMM1 ; XMM1 = { [B|0|0|0][G|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			cvttpd2dq XMM3, XMM3 ; XMM3 = { [R|0|0|0][A|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			pslldq XMM3, 8 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|0][0|0|0|0] }
			paddd XMM1, XMM3 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }		
			xorpd XMM3, XMM3 ; XMM3 = { [0] }		
			packusdw XMM1, XMM3 ; XMM1 = { [0|0|0|0][0|0|0|0][0|B|0|G][0|R|0|A] }   ; ESTO ES ILLEGAL!
			packuswb XMM1, XMM3 ; XMM1 = { [0|0|0|0][0|0|0|0][0|0|0|0][B|G|R|A] }

			pslldq XMM1, 8 ; XMM1 = { [0|0|0|0][0|0|0|0][B|G|R|A][0|0|0|0] }
			paddusb XMM4, XMM1 ; XMM4 = { [B|G|R|A][B|G|R|A][B|G|R|A][0|0|0|0] }
			inc R11
			;-----------------------------------------------------------------------------------------
			xor R14, R14
			xor R15, R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			cvtsi2sd XMM0, R11 ; XMM0 = COLUMNA ACTUAL
			cvtsi2sd XMM1, R10 ; XMM1 = FILA ACTUAL
			mulsd XMM0, [valor] ; XMM0 = COLUMNA ACTUAL * 255.5
			mulsd XMM1, [valor] ; XMM1 = FILA ACTUAL * 255.5
			cvtsi2sd XMM2, RDX ; XMM2 = COLUMNAS TOTALES
			cvtsi2sd XMM3, RCX ; XMM3 = FILAS TOTALES
			divsd XMM0, XMM2 ; XMM0 = (I*255.5)/COLUMNAS
			divsd XMM1, XMM3 ; XMM1 =  (J*255.5)/FILAS
			cvttsd2si R14, XMM0 ; R14 = (INT) (I*255.5)/COLUMNAS
			cvttsd2si R15, XMM1 ; R15 = (INT) (J*255.5)/FILAS
			xor R14, R15 ; R14 = R14 XOR R15
			xorpd XMM0, XMM0
			xorpd XMM1, XMM1
			xor R15, R15
			mov R15, 1
			;movq XMM0, R15
			cvtsi2sd XMM0, R15
			divsd XMM0, [valor] ; XMM0 = 1/255.0
			cvtsi2sd XMM1, R14
			mulsd XMM0, XMM1 ; XMM0 = COEF
			movdqu XMM2, XMM0 ; XMM2 = COEF
			pslldq XMM0, 8
			addsd XMM0, XMM2
			
			xorpd XMM2, XMM2		
			movdqu XMM1, [R12] ;XMM1 = { [R|G|B|A][R|G|B|A][R|G|B|A][R|G|B|A] }
			psrldq XMM1, 12 ;XMM1 = { [R|G|B|A][0|0|0|0][0|0|0|0][0|0|0|0] }
			xorpd XMM2, XMM2		
			punpcklbw XMM1, XMM2 ; XMM1 = { [0|B|0|G][0|R|0|A][0|B|0|G][0|R|0|A] }
			punpcklwd XMM1, XMM2 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			movdqu XMM3, XMM1 ; XMM3 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }
			psrldq XMM3, 8 ; XMM3 = { [0|0|0|R][0|0|0|A][0|0|0|0][0|0|0|0] }
			cvtdq2pd XMM1, XMM1 ; XMM1 = { [B|0|0|0][0|0|0|0][0|0|0|0][0|0|0|G] } DOUBLE
			cvtdq2pd XMM3, XMM3 ; XMM3 = { [R|0|0|0][0|0|0|0][0|0|0|0][0|0|0|A] } DOUBLE
			mulpd XMM1, XMM0 ; XMM1 = { [0|0|0|0][0|0|0|B][0|0|0|0][0|0|0|G] } * COEF
			mulpd XMM3, XMM0 ; XMM3 = { [0|0|0|0][0|0|0|R][0|0|0|0][0|0|0|A] } * COEF
			cvttpd2dq XMM1, XMM1 ; XMM1 = { [B|0|0|0][G|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			cvttpd2dq XMM3, XMM3 ; XMM3 = { [R|0|0|0][A|0|0|0][0|0|0|0][0|0|0|0] } CONVIERTO LOS DOUBLE EN INT
			pslldq XMM3, 8 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|0][0|0|0|0] }
			paddd XMM1, XMM3 ; XMM1 = { [0|0|0|B][0|0|0|G][0|0|0|R][0|0|0|A] }		
			xorpd XMM3, XMM3 ; XMM3 = { [0] }		
			packusdw XMM1, XMM3 ; XMM1 = { [0|0|0|0][0|0|0|0][0|B|0|G][0|R|0|A] }   ; ESTO ES ILLEGAL!
			packuswb XMM1, XMM3 ; XMM1 = { [0|0|0|0][0|0|0|0][0|0|0|0][B|G|R|A] }
			pslldq XMM1, 12 ; XMM1 = { [0|0|0|0][0|0|0|0][B|G|R|A][0|0|0|0] }
			paddusb XMM4, XMM1 ; XMM4 = { [B|G|R|A][B|G|R|A][B|G|R|A][B|G|R|A] }
			inc R11
			;----------------------------------------------------------------------------------------
			
			movdqu [R13], XMM4
			;add R11, 16
			lea R13, [R13+16]
			lea R12, [R12+16]
			jmp .cicloColumnas
		.finCicloColumnas:
		
		mov RAX, RDX
		add RAX, RAX
		add RAX, RAX ; RAX * 4
		sub RAX, R8
		lea R12, [R12+RAX]
		
		mov RAX, RDX
		add RAX, RAX
		add RAX, RAX ; RAX * 4
		sub RAX, R9
		lea R13, [R13+RAX]
		
		inc R10
		jmp .cicloFilas
	.finCicloFilas:
			
	; RDI = UNSIGNED CHAR *SRC
	; RSI = UNSIGNED CHAR *DST
	; RDX = INT COLS
	; RCX = INT ROWS
	; R8 = INT SRC_ROW_SIZE
	; R9 = INT DST_ROW_SIZE
			
	add RSP, 8
	pop R15
	pop R14
	pop R13
	pop R12
	pop RBX
	pop RBP
    ret
