; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

; Importa
extern GDT_DESC 
extern IDT_DESC	
extern pintarTablero
extern mmu_inicializar
extern idt_inicializar
extern mmu_inicializar_dir_zombie
extern mmu_mappear_pagina
extern mmu_unmappear_pagina
extern page_dir
extern habilitar_pic
extern deshabilitar_pic
extern resetear_pic
extern tss_inicializar
extern guardar_pantalla
extern restablecer_pantalla
extern pantalla_negra

; Exporta
global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0
 
    ; Habilitar A20
	call habilitar_A20

    ; Cargar la GDT
	lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0
    mov EAX, CR0
    or EAX, 1
    mov CR0, EAX

    ; Saltar a modo protegido
	jmp 0x40:modo_protegido
	bits 32
	modo_protegido:
	
    ; Establecer selectores de segmentos
	xor eax, eax
	mov ax, 1010000b
	mov ds, ax
	mov es, ax
	mov gs, ax
	mov ss, ax
    mov ax, 1100000b
 	mov fs, ax

	; Establecer la base de la pila
    mov esp, 0x27000
    mov ebp, 0x27000

    ; Imprimir mensaje de bienvenida
	
    ; Inicializar pantalla
    
    call pintarTablero
       
    ; Manejo de interrupciones
    LIDT [IDT_DESC]
	
    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    call mmu_inicializar
    
    ; Cargar directorio de paginas
    mov eax, [page_dir]
    mov cr3, eax

    ; Habilitar paginacion
    mov EAX, CR0
    or EAX, 0x80000000
    mov CR0, EAX    
    
    ; Inicializar tss
    call tss_inicializar

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    CALL idt_inicializar    
    
    call deshabilitar_pic
    call resetear_pic
    call habilitar_pic
    sti

    ; Cargar IDT

    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial
    mov ax, (0xD*8)
    ltr ax

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle
	mov ax, (0xE*8)
    jmp (0xE*8):0

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
