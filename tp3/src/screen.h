/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80
#define mem_vid 0xb8000



#include "colors.h"
#include "defines.h"
/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

typedef struct str_memoria_video {
	unsigned char   ascii:8;
	unsigned char   caracter:3;
	unsigned char   brillante:1;
	unsigned char   fondo:3;
	unsigned char   blink:1; 
} __attribute__((__packed__)) memoria_video;

void pintarTablero();
void mostrar_int(int error);
void print_keyboar_int(unsigned int scanCode);
void pintarDebugger();
void restablecer_pantalla();
void guardar_pantalla();
const char* dame_numero(int n);
void pantalla_negra();
void memcopy(unsigned char* source, unsigned char* dst, int tam);
#endif  /* !__SCREEN_H__ */
