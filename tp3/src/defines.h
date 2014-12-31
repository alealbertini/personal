/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define SIZE_W                  78
#define SIZE_H                  44


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 31

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CODIGO_KERNEL		8
#define GDT_IDX_CODIGO_USUARIO		9
#define GDT_IDX_DATOS_KERNEL		10
#define GDT_IDX_DATOS_USUARIO		11
#define GDT_IDX_DATOS_VIDEO			12
#define GDT_IDX_TSS_INICIAL			13
#define GDT_IDX_TSS_IDLE			14
#define GDT_IDX_TSS_ZOMBIE_A1		15
#define GDT_IDX_TSS_ZOMBIE_A2		16
#define GDT_IDX_TSS_ZOMBIE_A3		17
#define GDT_IDX_TSS_ZOMBIE_A4		18
#define GDT_IDX_TSS_ZOMBIE_A5		19
#define GDT_IDX_TSS_ZOMBIE_A6		20
#define GDT_IDX_TSS_ZOMBIE_A7		21
#define GDT_IDX_TSS_ZOMBIE_A8		22
#define GDT_IDX_TSS_ZOMBIE_B1		23
#define GDT_IDX_TSS_ZOMBIE_B2		24
#define GDT_IDX_TSS_ZOMBIE_B3		25
#define GDT_IDX_TSS_ZOMBIE_B4		26
#define GDT_IDX_TSS_ZOMBIE_B5		27
#define GDT_IDX_TSS_ZOMBIE_B6		28
#define GDT_IDX_TSS_ZOMBIE_B7		29
#define GDT_IDX_TSS_ZOMBIE_B8		30

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */

//void* page_libre = (void*) 0x100000;


#endif  /* !__DEFINES_H__ */
