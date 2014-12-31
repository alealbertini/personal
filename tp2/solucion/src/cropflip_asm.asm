global cropflip_asm

section .text
;void tiles_asm(unsigned char *src,
;              unsigned char *dst,
;		int cols, rows
;              int src_row_size,
;              int dst_row_size,
;		int tamx, int tamy,
;		int offsetx, int offsety);

cropflip_asm:
	;RDI = UNSIGNED CHAR *SRC
	;RSI = UNSIGNED CHAR *DST
	;RDX = INT COLS
	;RCX = INT ROWS
	;R8 = INT SRC_ROW_SIZE
	;R9 = INT DST_ROW_SIZE
	;
	;
	push RBP
	mov RBP, RSP
	push RBX
	push R12
	push R13
	push R14
	push R15
	sub RSP, 8
	; TAMX = [RSP+64]
	; TAMY = [RSP+72]
	; OFFSETX = [RSP+80]
	; OFFSETY = [RSP+88]
	
	mov R12, RDI ; R12 = UNSIGNED CHAR *SRC
	mov R13, RSI ; R13 = UNSIGNED CHAR *DST	
	xor RAX, RAX
	mov EAX, [RSP+88] ; RAX = OFFSETY
	add EAX, [RSP+72] ; RAX = OFFSETY + TAMY
	dec RAX
	xor R14, R14
	mov R14, R8
	mul R14 ; RAX = CANTIDAD DE BYTES A AVANZAR PARA LLEGAR A LA FILA DONDE TERMINA EL RECUADRO
	lea R12, [R12+RAX] ; R12 = UNSIGNED CHAR *SRC - ME POSICIONO EN LA ULTIMA FILA DEL RECUADRO A COPIAR
	xor R10, R10
	xor RAX, RAX
	mov R10D, 4
	mov EAX, [RSP+80] ; RAX = OFFSETX
	;add EAX, [RSP+64] ; RAX = OFFSETX + TAMX
	mul R10 ; RAX = CANTIDAD DE BYTES A AVANZAR EN LAS COLUMNAS
	lea R12, [R12+RAX] ; R12 = AVANZO AL INICIO DEL RECUADRO DE LAS COLUMNAS 
	
	xor R10, R10
	
	.cicloFilas:
		cmp R10D, [RSP+72] ; VEO SI LLEGO AL FINAL DEL RECUADRO EN FILAS
		jae .finCicloFilas
		xor R11, R11
		.cicloColumnas:
			cmp R11D, [RSP+64]
			jae .finCicloColumnas
			

			mov rax, [rsp]
			mov rax, [rsp]
			mov [rsp+8], rax
			mov [rsp+8], rax			
			mov rax, [rsp]
			mov rax, [rsp]
			mov [rsp+8], rax
			mov [rsp+8], rax

			mov rax, [rsp]
			mov rax, [rsp]
			mov [rsp+8], rax
			mov [rsp+8], rax			
			mov rax, [rsp]
			mov rax, [rsp]
			mov [rsp+8], rax
			mov [rsp+8], rax


			movdqu XMM0, [R12]
			movdqu [R13], XMM0
			add R11, 4
			lea R12,[R12+16]
			lea R13,[R13+16]
			jmp .cicloColumnas
		.finCicloColumnas:
	
		xor RAX, RAX
		mov EAX, [RSP+64] ;RAX = TAMX
		xor R14, R14
		mov R14D, 4
		mul R14 ; RAX = TAMX * 4
		mov R15, R9 ; R15 = INT DST_ROW_SIZE
		sub R15, RAX ; R15 = INT DST_ROW_SIZE - TAMX * 4
		lea R13, [R13+R15]
				
		inc R10
		xor RAX, RAX
		mov EAX, [RSP+72] ; RAX = TAMY
		add EAX, [RSP+88] ; RAX = TAMY * OFFSETY
		sub RAX, R10
		dec RAX
		mov R14, R8 ; R14 = INT SRC_ROW_SIZE
		mul R14 ;RAX = SRC_ROW_SIZE * TAMY * OFFSETY
		mov R15, RAX ;R15 = DST_ROW_SIZE * TAMY * OFFSETY (FINAL DEL RECUADRO A COPIAR)
		
		lea R12,[RDI]
		lea R12, [R12+R15] ;VOY A LA FILA ACTUAL
		mov EAX, [RSP+80] ; RAX = OFFSETX
		;add EAX, [RSP+64] ; RAX = TAMX + OFFSETX
		mov R14D, 4 
		mul R14 ; RAX = OFFSETX * 4
		lea R12, [R12+RAX]
		;;;;;;;;;;;;
		; TAMX = [RSP+64]
		; TAMY = [RSP+72]
		; OFFSETX = [RSP+80]
		; OFFSETY = [RSP+88]
		
		jmp .cicloFilas
	.finCicloFilas:
	add RSP, 8
	pop R15
	pop R14
	pop R13
	pop R12
	pop RBX
	pop RBP
    ret
