/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"

unsigned short sched_proximo_indice();
void mapear_contorno_A(int c, int f, unsigned int cr3, unsigned char attrs);
void mapear_contorno_B(int c, int f, unsigned int cr3, unsigned char attrs);
const char * clase_zombie(int t);
const char * clase_zombie_aux(int t);
unsigned int codigo_tarea(unsigned int tipo);
void pintar_tarea();
#endif	/* !__SCHED_H__ */
