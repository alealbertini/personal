; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00
modo_debug: dd 0x00
debug_activado: db 0x00
entro_excepcion: dd 0x00

;; PIC
extern fin_intr_pic1
extern mostrar_int

;; IMPORTA
extern print_debug_mode
extern print_keyboar_int
extern pintarDebugger
extern restablecer_pantalla
extern guardar_pantalla
extern mmu_inicializar_dir_zombie
extern mmu_mappear_pagina
extern tss_inicializar_zombie
extern sched_proximo_indice
extern setear_tipo_zombie
extern crear_zombie
extern mover_zombie
extern mover_jugador
extern zombie_en_uso
extern desalojar_tarea
extern pintar_tarea
;; Sched
extern sched_proximo_indice

;; EXPORTA
global _isr32
global _isr33
global _isr102

offset : dd 0
selector : dw 0
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    push eax
    call mostrar_int 
    pop eax
    
    
    mov dword [entro_excepcion], 1
    

    cmp byte[modo_debug], 0x0
    je .noDebug
    mov byte[debug_activado], 1
    call guardar_pantalla
    push esp
    push esp
    push esp
    push esp
    push esp
    pushfd
    push ss
    push gs
    push fs
    push es
    push ds
    push cs
    call .push_eip
    .push_eip:
    push esp
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax    
    call pintarDebugger
    call pintar_tarea    
	add esp, 80
    
    
    sti
    
    .noDebug:
    call desalojar_tarea
    call zombie_en_uso
    ; Saltar a la primera tarea: Idle
    mov ax, 14*0x8
    mov [selector], ax
    jmp far [offset]
	
    ;mov eax, 0xFFFF
    ;mov ebx, 0xFFFF
    ;mov ecx, 0xFFFF
    ;mov edx, 0xFFFF
    ;jmp $
    ;jmp $
    

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

;global _isr14
;_isr14:
 ;   xchg bx, bx
;    iret

;global _isr15
;_isr15:
    ;xchg bx, bx
;    iret

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
_isr32:
    pushad    
    cli
    cmp byte [debug_activado], 1
    je .nojump
    
    call proximo_reloj    
    call sched_proximo_indice ; ME DEVUELVE EN EAX EL SELECTOR DE LA GDT DE LA TAREA A SALTAR
    cmp ax, 8
    je .nojump

    mov [selector], ax
    call fin_intr_pic1
    jmp far [offset]
    jmp .end
    ;jmp far LOGICA
    .nojump:
    call fin_intr_pic1
    
    .end:
;   sti
    popad
    iret


;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
    pushad
    cli 
    xor eax, eax
    in al, 0x60
    mov edi, eax

    cmp edi, 0x15
    jne .noEsDebugger

    cmp byte [debug_activado], 1
    je .restablecer_pantalla

    xor eax, eax
    mov al, byte[modo_debug]
    xor al, 0x1
    mov byte[modo_debug], al
    
    jmp .fin

.restablecer_pantalla:
    mov dword [entro_excepcion], 0
    mov dword [debug_activado], 0
    call restablecer_pantalla
    jmp .fin

.noEsDebugger:
	cmp byte [debug_activado], 1
	je .fin
	
    push edi
    call print_keyboar_int
    pop edi

    push edi
    call setear_tipo_zombie
    pop edi
    
    push edi
    ;xchg bx, bx
    call crear_zombie
    pop edi
    
    push edi
    call mover_jugador
    pop edi

.fin:
    push dword[modo_debug]
    call print_debug_mode
    add esp, 4

    call fin_intr_pic1
    popad
    iret


;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define IZQ 0xAAA
%define DER 0x441
%define ADE 0x83D
%define ATR 0x732



_isr102:
    pushad
    cli
    push eax
    call mover_zombie
    pop eax
    xor eax, eax
    mov ax, 14*0x8
    mov [selector], ax
    call fin_intr_pic1
    jmp far [offset]
    call zombie_en_uso
    popad
    iret


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
