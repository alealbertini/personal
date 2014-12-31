global mblur_asm
section .data
constante:
dd 0.2, 0.2, 0.2, 0.2
section .text
;void mblur_asm (
;unsigned char *src, RDI
;unsigned char *dst, RSI
;int cols, EDX
;int filas, ECX
;int src_row_size, R8d
;int dst_row_size) R9d
mblur_asm:
	push rbp ; A
	mov rbp, rsp
	push r12 ; D
	push r13 ; A
	push r14 ; D
	push r15 ; A
	push rbx ; D
	
	sub rsp, 8 ; A
	%define src rdi
	%define dst rsi
	
	mov r12d, ecx
	%define filas r12
	
	mov r13d, edx
	%define cols r13
	
	mov r8d, r8d
	%define sRSize r8
	
	xor r15, r15
	xor r14, r14
	%define i rbx
	%define j rcx
	
	mov i, 0 ; empiezo a iterar las filas y columnas desde 0
	mov j, 0
	
	movdqu xmm12, [constante]
	%define const xmm12


.loopF1: ; PINTA LAS PRIMERAS 2 FILAS
	cmp i, 2
	jge .loopF2
.loopC1:
	cmp j, cols
	jge .ProxFila1
	xorpd xmm0, xmm0
.escribir1:
	movdqu [dst+r15], xmm0
	add j, 4
	add r15, 16 ; Avanzamos 1 px = 4 bytes
	jmp .loopC1
.ProxFila1:
	inc i ; fila++
	mov j, 0 ; col = 2
	mov r15, r14 ; r15 = i * src_row_size
	add r15, 8 ; 8 px del borde.
	add r14, sRSize ; r10 += src_row_size
	jmp .loopF1
	
	
.loopF2: ; PINTA LAS ULTIMAS 2 FILAS
	mov i, filas
	sub i, 2
.ciclo2:
	cmp i, filas
	jge .loopF3 ; esBorde
.loopC2:
	cmp j, cols
	jge .ProxFila2 ; j < columnas?
	xorpd xmm0, xmm0
.escribir2:
	movdqu [dst+r15], xmm0
	add j, 4
	add r15, 16 ; Avanzamos 1 px = 4 bytes
	jmp .loopC2
.ProxFila2:
	inc i ; fila++
	mov j, 0 ; col = 2
	mov r15, r14 ; r15 = i * src_row_size
	add r15, 8 ; 8 px del borde.
	add r14, sRSize ; r10 += src_row_size
	jmp .ciclo2
	
	
.loopF3: ; PINTA LAS PRIMERAS 2 COLUMNAS
	mov i, 2
	mov j, 0
	sub filas, 2
.ciclo3:
	cmp i, filas
	;jg .loopF4 ; esBorde
	jg .pintarResto
.loopC3:
	cmp j, 2
	jge .ProxFila3 ; j < columnas?
	xorpd xmm0, xmm0
.escribir3:
	movdqu [dst+r15], xmm0
	add j, 4
	add r15, 16 ; Avanzamos 1 px = 4 bytes
	jmp .loopC3
.ProxFila3:
	inc i ; fila++
	mov j, 0 ; col = 2
	mov r15, r14 ; r15 = i * src_row_size
	add r15, 8 ; 8 px del borde.
	add r14, sRSize ; r10 += src_row_size
	jmp .ciclo3
	
	
.loopF4: ; PINTA LAS ULTIMAS 2 COLUMNAS
	mov i, 2
	mov j, cols
	sub j, 2
.ciclo4:
	cmp i, filas
	jge .pintarResto
.loopC4:
	cmp j, cols
	jge .ProxFila4
	xorpd xmm0, xmm0
.escribir4:
	movq [dst+r15], xmm0
	add j, 2   ; 
	add r15, 8 ; Avanzamos 1 px = 4 bytes
	jmp .loopC4
.ProxFila4:
	inc i ; fila++
	mov j, cols ;
	sub j, 2
	mov r15, r14 ; r15 = i * src_row_size
	;add r15, 8 ; 8 px del borde.
	add r14, sRSize ; r10 += src_row_size
	jmp .ciclo4
	
	
.pintarResto:
	xor r14, r14
	xor r15, r15 ; r15 = (fila*src_row_size) + (pixel * 8) [byte]
	add r15, sRSize
	add r15, sRSize
	mov r14, r15 ; r14 son los múltiplos de src row size. (sirve para armar el puntero de r15).
	add r15, 8 ; r15 arranca la fila 2, col 2.
	mov i, 2 ; empiezo a iterar las filas y columnas desde 2
	mov j, 2
	sub cols, 2
	
	
.loopF:
	cmp i, filas ; i < filas?
	jg .fin ; esBorde
.loopC:
	  cmp j, cols
	  jge .ProxFila ; j < columnas?
	  pxor xmm7, xmm7
	  movq xmm0, [src+r15] ; xmm0 = 00 | 00 | p1 | p0
	  sub r15, sRSize
	  sub r15, sRSize
	  sub r15, 8
	  movq xmm1, [src+r15] ; xmm1 = 00 | 00 | p3 | p2
	  add r15, sRSize
	  add r15, 4
	  movq xmm2, [src+r15] ; xmm2 = 00 | 00 | p5 | p4
	  add r15, sRSize
	  add r15, sRSize
	  add r15, 8
	  movq xmm3, [src+r15] ; xmm3 = 00 | 00 | p7 | p6
	  add r15, sRSize
	  add r15, 4
	  movq xmm4, [src+r15] ; xmm4 = 00 | 00 | p9 | p8
	  sub r15, sRSize
	  sub r15, sRSize
	  sub r15, 8
	  punpcklbw xmm0, xmm7 ; xmm0 = [00 B1 00 G1 00 R1 00 A1 00 B0 00 G0 00 R0 00 A0] WORD
	  punpcklbw xmm1, xmm7 ; xmm1 = [00 B3 00 G3 00 R3 00 A3 00 B2 00 G2 00 R2 00 A2] WORD
	  punpcklbw xmm2, xmm7 ; xmm2 = [00 B5 00 G5 00 R5 00 A5 00 B4 00 G4 00 R4 00 A4] WORD
	  punpcklbw xmm3, xmm7 ; xmm3 = [00 B7 00 G7 00 R7 00 A7 00 B6 00 G6 00 R6 00 A6] WORD
	  punpcklbw xmm4, xmm7 ; xmm4 = [00 B9 00 G9 00 R9 00 A9 00 B8 00 G8 00 R8 00 A8] WORD
	  paddw xmm0, xmm1 ; xmm0 = [0 B1+B3 0 G1+G3 0 R1+R3 0 A1+A3 0 B0+B2 0 G0+G2 0 R0+R2 0 A0+A2] WORD
	  paddw xmm0, xmm2 ; xmm0 = [0 B1+B3+B5 0 G1+G3+G5 0 R1+R3+R5 0 A1+A3+A5 0 B0+B2+B4 0 G0+G2+G4 0 R0+R2+R4 0 A0+A2+A4] WORD
	  paddw xmm0, xmm3 ; xmm0 = [0 B1+B3+B5+B7 0 G1+G3+G5+G7 0 R1+R3+R5+R7 0 A1+A3+A5+A7 0 B0+B2+B4+B6 0 G0+G2+G4+G6 0 R0+R2+R4+R6 0 A0+A2+A4+A6] WORD
	  paddw xmm0, xmm4 ; xmm0 = [0 B1+B3+B5+B7+B9 0 G1+G3+G5+G7+G9 0 R1+R3+R5+R7+R9 0 A1+A3+A5+A7+A9 0 B0+B2+B4+B6+B8 0 G0+G2+G4+G6+G8 0 R0+R2+R4+R6+R8 0 A0+A2+A4+A6+A8] WORD
	  pxor xmm5, xmm5
	  movdqu xmm5, xmm0
	  ;pand xmm5, [parteAlta] ; me quedo con la parte alta de xmm5
	  PSRLDQ xmm5, 8 ; xmm5 = [0 0 0 0 0 B1+B3+B5+B7+B9 0 G1+G3+G5+G7+G9 0 R1+R3+R5+R7+R9 0 A1+A3+A5+A7+A9] WORD
	  PSLLDQ xmm0, 8 ; xmm0 = [0 0 0 0 0 B0+B2+B4+B6+B8 G0+G2+G4+G6+G8 R0+R2+R4+R6+R8 A0+A2+A4+A6+A8] WORD
	  PSRLDQ xmm0, 8 ; xmm0 = [0 0 0 0 0 B0+B2+B4+B6+B8 G0+G2+G4+G6+G8 R0+R2+R4+R6+R8 A0+A2+A4+A6+A8] WORD
	  punpcklwd xmm0, xmm7 ; xmm0 = [B0+B2+B4+B6+B8 G0+G2+G4+G6+G8 R0+R2+R4+R6+R8 A0+A2+A4+A6+A8] DOUBLE WORD
	  punpcklwd xmm5, xmm7 ; xmm5 = [B1+B3+B5+B7+B9 G1+G3+G5+G7+G9 R1+R3+R5+R7+R9 A1+A3+A5+A7+A9] DOUBLE WORD
	  CVTDQ2PS xmm0, xmm0 ; convierto dword int a dword float
	  CVTDQ2PS xmm5, xmm5 ; convierto dword int a dword float
	  mulps xmm0, const ; multiplico 4 floats por 0,2
	  mulps xmm5, const ; multiplico 4 floats por 0,2
	  CVTPS2DQ xmm0, xmm0 ; convierto dword float a dword inT
	  CVTPS2DQ xmm5, xmm5 ; convierto dword float a dword int
	  PACKUSDW xmm0, xmm7 ; xmm0 = [00 00 00 00 B0 G0 R0 A0] WORD
	  PACKUSDW xmm5, xmm7 ; xmm5 = [00 00 00 00 B0 G0 R0 A0] WORD
	  PACKUSWB xmm0, xmm7 ; xmm0 = [00 00 00 00 B0 G0 R0 A0] BYTE
	  PACKUSWB xmm5, xmm7 ; xmm5 = [00 00 00 00 B0 G0 R0 A0] BYTE
	  PSLLDQ xmm5, 4
	  paddb xmm0, xmm5
.escribir:
	  movq [dst+r15], xmm0
	  add j, 2
	  add r15, 8 ; Avanzamos 1 px = 4 bytes
	  jmp .loopC
.ProxFila:
	  inc i ; fila++
	  mov j, 2 ; col = 2
	  mov r15, r14 ; r15 = i * src_row_size
	  add r15, 8 ; 8 px del borde.
	  add r14, sRSize ; r10 += src_row_size
	  jmp .loopF
.fin:
	  add rsp, 8 ; A
	  pop rbx ; D
	  pop r15 ; A
	  pop r14 ; D
	  pop r13 ; A
	  pop r12 ; D
	  pop rbp ; A
	  ret
