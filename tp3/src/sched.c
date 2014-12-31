/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

int jugador_actual = 0;
int tarea_actualA = 0;							// El numero de tarea actual del A en tss_zombisA
int tarea_actualB = 0;							// El numero de tarea actual del B en tss_zombisB
int posicion_zombie_A_C[CANT_ZOMBIS];				// La posicion en columnas de las tareas_A
int posicion_zombie_B_C[CANT_ZOMBIS];				// La posicion en columnas de las tareas_B
int posicion_zombie_A_F[CANT_ZOMBIS];				// La posicion en filas de las tareas_A
int posicion_zombie_B_F[CANT_ZOMBIS];				// La posicion en filas de las tareas_B
int clase_zombie_A[CANT_ZOMBIS];				// La clase de cada zombie del jugador A
int clase_zombie_B[CANT_ZOMBIS];				// La clase de cada zombie del jugador B
int posicion_jugador_A = 1;						// La posicion (Y) en el mapa
int posicion_jugador_B = 1;						// La posicion (Y) en el mapa
int tipo_zombie_A = 0;
int tipo_zombie_B = 0;
extern tss* tss_zombisA;
extern tss* tss_zombisB;
extern const char* dame_numero(int n);
unsigned int cr3_A[CANT_ZOMBIS];
unsigned int cr3_B[CANT_ZOMBIS];
unsigned int puntos_jugador_A = 0;
unsigned int puntos_jugador_B = 0;
unsigned int zombies_restantes_A = 20;
unsigned int zombies_restantes_B = 20;

void inicializar_sched() 
{
	/*	jugador_actual = 0;		     // ¿ELIJO UN JUGADOR AL AZAR? CREO QUE HAY Q ELEGIR A 1 JUGADOR SI O SI
	tarea_actualA = 0;			
	tarea_actualB = 0;
	int i;
	for (i = 0; i < CANT_ZOMBIS; i++)
	{
		posicion_zombie_A[i] = 0x50000;
		posicion_zombie_B[i] = 0x9F000;	
	}*/
}


unsigned short sched_proximo_indice()
{
	int i;
	if (jugador_actual == 1) //jugador A
	{
		tarea_actualA = (tarea_actualA + 1) % 8;
		jugador_actual = 0;
		for (i = 0; i < 8; ++i)
		{
			int pos = (i + tarea_actualA) % 8;
			if (tareas_A[pos] == 1)
			{			
					tarea_actualA = pos;
					return (pos + 15)*8;
			}
		}
		
	}
	else
	{
		tarea_actualB = (tarea_actualB + 1) % 8;
		jugador_actual = 1;
		for (i = 0; i < 8; ++i)
		{
			int pos = (i + tarea_actualB) % 8;
			if (tareas_B[pos] == 1)
			{				
					tarea_actualB = pos;
					return (pos + 23)*8;
			}
		}
	}

	return 8;
}

void mover_zombie(unsigned int direccion)
{
	// Establezco la nueva direccion del zombie
	unsigned int posicion_zombie_C;
	unsigned int posicion_zombie_F;
	unsigned int cr3;

	if (jugador_actual == 0) //jugador A
	{
		posicion_zombie_C = posicion_zombie_A_C[tarea_actualA];
		posicion_zombie_F = posicion_zombie_A_F[tarea_actualA];

		switch (direccion)
		{
			case ADE: // Adelante
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				posicion_zombie_C++;
				posicion_zombie_A_C[tarea_actualA] = posicion_zombie_C;				
				print(clase_zombie(clase_zombie_A[tarea_actualA]), posicion_zombie_C, posicion_zombie_F , 0x4F);
				//breakpoint();
				copiar_pagina_4k((unsigned int*)0x8001000, (unsigned int*) 0x8000000);
				break;
			case 0x732: // Atras
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				posicion_zombie_C--;
				posicion_zombie_A_C[tarea_actualA] = posicion_zombie_C;
				print(clase_zombie(clase_zombie_A[tarea_actualA]), posicion_zombie_C, posicion_zombie_F , 0x4F);
				copiar_pagina_4k((unsigned int*)0x8006000, (unsigned int*) 0x8000000);
				break;
			case 0xAAA: // Izq
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				if (posicion_zombie_F == 1)
				{
					posicion_zombie_F = 44;
				}
				else
				{
					posicion_zombie_F--;
				}
				posicion_zombie_A_F[tarea_actualA] = posicion_zombie_F;
				print(clase_zombie(clase_zombie_A[tarea_actualA]), posicion_zombie_C, posicion_zombie_F , 0x4F);
				copiar_pagina_4k((unsigned int*)0x8005000, (unsigned int*) 0x8000000);
				break;
			case 0x441: // Der
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				//breakpoint();
				if (posicion_zombie_F == 44)
				{
					posicion_zombie_F = 1;
				}
				else
				{
					posicion_zombie_F++;
				}
				posicion_zombie_A_F[tarea_actualA] = posicion_zombie_F;
				print(clase_zombie(clase_zombie_A[tarea_actualA]), posicion_zombie_C, posicion_zombie_F , 0x4F);
				copiar_pagina_4k((unsigned int*)0x8004000, (unsigned int*) 0x8000000);
				break;
		}
		cr3 = cr3_A[tarea_actualA];
		mmu_mappear_pagina(0x8000000, cr3, dame_fisica(posicion_zombie_C, posicion_zombie_F), 1);
		mapear_contorno_A(posicion_zombie_C, posicion_zombie_F, cr3, 1);
		if(posicion_zombie_C == 78)
		{
			print(" ", posicion_zombie_C, posicion_zombie_F  , 0x22);
			puntos_jugador_A++;
			print(dame_numero(puntos_jugador_A), 33, 47, 0x4F);
			tareas_A[tarea_actualA] = 0;
		} 
		if(posicion_zombie_C == 1)
		{
			print(" ", posicion_zombie_C, posicion_zombie_F  , 0x22);
			puntos_jugador_B++;
			print(dame_numero(puntos_jugador_B), 38, 47, 0x4F);
			tareas_A[tarea_actualA] = 0;
		}  
		//tarea_actualA = (tarea_actualA + 1) % 8;
	}
	else
	{ 
		posicion_zombie_C = posicion_zombie_B_C[tarea_actualB];
		posicion_zombie_F = posicion_zombie_B_F[tarea_actualB];
		switch (direccion)
		{
			case 0x83D: // Adelante
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				posicion_zombie_C--;
				posicion_zombie_B_C[tarea_actualB] = posicion_zombie_C;				
				print(clase_zombie(clase_zombie_B[tarea_actualB]), posicion_zombie_C, posicion_zombie_F , 0x1F);
				copiar_pagina_4k((unsigned int*)0x8001000, (unsigned int*) 0x8000000);
				break;
			case 0x732: // Atras
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				posicion_zombie_C++;
				posicion_zombie_B_C[tarea_actualB] = posicion_zombie_C;
				print(clase_zombie(clase_zombie_B[tarea_actualB]), posicion_zombie_C, posicion_zombie_F , 0x1F);
				copiar_pagina_4k((unsigned int*)0x8006000, (unsigned int*) 0x8000000);
				break;
			case 0xAAA: // Izq
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				if (posicion_zombie_F == 44)
				{
					posicion_zombie_F = 1;
				}
				else
				{
					posicion_zombie_F++;
				}
				posicion_zombie_B_F[tarea_actualB] = posicion_zombie_F;
				print(clase_zombie(clase_zombie_B[tarea_actualB]), posicion_zombie_C, posicion_zombie_F , 0x1F);
				copiar_pagina_4k((unsigned int*)0x8005000, (unsigned int*) 0x8000000);
				break;
			case 0x441: // Der
				print("X", posicion_zombie_C, posicion_zombie_F  , 0x70);
				if (posicion_zombie_F == 1)
				{
					posicion_zombie_F = 44;
				}
				else
				{
					posicion_zombie_F--;
				}
				posicion_zombie_B_F[tarea_actualB] = posicion_zombie_F;
				print(clase_zombie(clase_zombie_B[tarea_actualB]), posicion_zombie_C, posicion_zombie_F , 0x1F);
				copiar_pagina_4k((unsigned int*)0x8004000, (unsigned int*) 0x8000000);
				break;
		}
		// TODO: mover al zombie en posicion ambie B	
		cr3 = cr3_B[tarea_actualB];
		mmu_mappear_pagina(0x8000000, cr3, dame_fisica(posicion_zombie_C, posicion_zombie_F), 1);
		mapear_contorno_B(posicion_zombie_C, posicion_zombie_F, cr3, 1);  
		if(posicion_zombie_C == 1)
		{
			print(" ", posicion_zombie_C, posicion_zombie_F  , 0x22);
			puntos_jugador_B++;
			print(dame_numero(puntos_jugador_B), 38, 47, 0x4F);
			tareas_B[tarea_actualB] = 0;
		}
		if(posicion_zombie_C == 78)
		{
			print(" ", posicion_zombie_C, posicion_zombie_F  , 0x22);
			puntos_jugador_A++;
			print(dame_numero(puntos_jugador_A), 33, 47, 0x4F);
			tareas_B[tarea_actualB] = 0;
		}  
		//tarea_actualB = (tarea_actualB + 1) % 8;
	}
	zombie_en_uso();

}

void mapear_contorno_A(int c, int f, unsigned int cr3, unsigned char attrs)
{
	int filaAnt;
	int filaSig;
	if (f == 44){filaSig = 1;}else{filaSig = f+1;}
	mmu_mappear_pagina((unsigned int)0x8002000, cr3, dame_fisica(c+1, filaSig), attrs);
	mmu_mappear_pagina((unsigned int)0x8008000, cr3, dame_fisica(c-1, filaSig), attrs);
	mmu_mappear_pagina((unsigned int)0x8004000, cr3, dame_fisica(c, filaSig),	attrs);
	if (f == 1){filaAnt = 44;}else{filaAnt = f-1;}
	mmu_mappear_pagina((unsigned int)0x8003000, cr3, dame_fisica(c+1, filaAnt),	attrs);
	mmu_mappear_pagina((unsigned int)0x8007000, cr3, dame_fisica(c-1, filaAnt), attrs);
	mmu_mappear_pagina((unsigned int)0x8005000, cr3, dame_fisica(c, filaAnt),	attrs);
	mmu_mappear_pagina((unsigned int)0x8001000, cr3, dame_fisica(c+1, f), attrs);
	mmu_mappear_pagina((unsigned int)0x8006000, cr3, dame_fisica(c-1, f), attrs);
}

void mapear_contorno_B(int c, int f, unsigned int cr3, unsigned char attrs)
{
	int filaAnt;
	int filaSig;
	if (f == 1){filaAnt = 44;}else{filaAnt = f-1;}
	mmu_mappear_pagina((unsigned int)0x8004000, cr3, dame_fisica(c, filaAnt),	attrs);
	mmu_mappear_pagina((unsigned int)0x8002000, cr3, dame_fisica(c-1, filaAnt), attrs);
	mmu_mappear_pagina((unsigned int)0x8008000, cr3, dame_fisica(c+1, filaAnt), attrs);
	if (f == 44){filaSig = 1;}else{filaSig = f+1;}
	mmu_mappear_pagina((unsigned int)0x8005000, cr3, dame_fisica(c, filaSig),	attrs);
	mmu_mappear_pagina((unsigned int)0x8003000, cr3, dame_fisica(c-1, filaSig),	attrs);
	mmu_mappear_pagina((unsigned int)0x8007000, cr3, dame_fisica(c+1, filaSig), attrs);
	mmu_mappear_pagina((unsigned int)0x8001000, cr3, dame_fisica(c-1, f), attrs);
	mmu_mappear_pagina((unsigned int)0x8006000, cr3, dame_fisica(c+1, f), attrs);
}

void setear_tipo_zombie(unsigned int tecla)
{
	switch (tecla)
	{
		case 0x1e: //a
			tipo_zombie_A = (tipo_zombie_A + 2) % 3;
			print(clase_zombie(tipo_zombie_A), 0, posicion_jugador_A, 0x4F);
			break;
		case 0x20: //d
			tipo_zombie_A = (tipo_zombie_A + 1) % 3;
			print(clase_zombie(tipo_zombie_A), 0, posicion_jugador_A, 0x4F);
			break;
		case 0x24: //j
			tipo_zombie_B = (tipo_zombie_B + 2) % 3;
			print(clase_zombie(tipo_zombie_B), 79, posicion_jugador_B, 0x1F);
			break;
		case 0x26: //l
			tipo_zombie_B = (tipo_zombie_B + 1) % 3;
			print(clase_zombie(tipo_zombie_B), 79, posicion_jugador_B, 0x1F);
			break;
		default:
			//print("NO ES UNA TECLA VALIDA", 0, 0, 0xf);   
			break;
	}	
}

void crear_zombie(unsigned int tecla)
{
	/*  ;1) mmu_inicializar_dir_zombie CREO LA PD Y PT DEL ZOMBIE PARA EL IDENTITY MAPPING
    ;2) mmu_mappear_pagina MAPEO LA DIRECCION FISICA QUE CORRESPONDE
    ;3) COPIO EL CODIGO DE LA TAREA DEL ZOMBIE EN LA FISICA QUE CORRESPONDE
    ;4) CREO LA TSS DEL ZOMBIE
    ;if lshift then 
        ;if (hay_zombies_sin_inicializar)
            ;call mmu_inicializar_dir_zombie(jugador A)
            ;mov r8d, 0x0
            ;mov r9d, 
            ;call mmu_mappear_pagina
            ;call tss_inicializar_zombie(jugador A)

    ;if rshift then 
        ;if (hay_zombies_sin_inicializar)
            ;call mmu_inicializar_dir_zombie(jugador B)
            ;call mmu_mappear_pagina
            ;call tss_inicializar_zombie(jugador B)
	*/
	switch (tecla)
	{
		case 0x2a: //lshift
			if(zombies_restantes_A != 0)
			{
				if (primer_pos_libre(tareas_A) != 8)	// Esto significa que hay lugar libre
				{
					unsigned int fisica_nuevo_zombie = dame_fisica(2, posicion_jugador_A);
					posicion_zombie_A_F[primer_pos_libre(tareas_A)] = posicion_jugador_A;
					posicion_zombie_A_C[primer_pos_libre(tareas_A)] = 2;
					clase_zombie_A[primer_pos_libre(tareas_A)] = tipo_zombie_A;
					unsigned int cr3 = (unsigned int)mmu_inicializar_dir_zombie();
					cr3_A[primer_pos_libre(tareas_A)] = cr3;
					mmu_mappear_pagina(0x8000000, cr3, fisica_nuevo_zombie, 1);
					mapear_contorno_A(posicion_zombie_A_C[primer_pos_libre(tareas_A)], posicion_zombie_A_F[primer_pos_libre(tareas_A)], cr3, 1);
					unsigned int cr3_actual = rcr3();
					mmu_mappear_pagina(0x9000000, cr3_actual, fisica_nuevo_zombie, 1); //TODO: CAMBIAR ESTO
					unsigned int fisica_codigo_zombie = 0x10000 + tipo_zombie_A*0x1000;
					copiar_pagina_4k((unsigned int*)0x9000000, (unsigned int*)fisica_codigo_zombie);
					mmu_unmappear_pagina(0x9000000, cr3_actual);
					tss_inicializar_zombie(0, cr3);
					print(clase_zombie(tipo_zombie_A), 2, posicion_jugador_A, 0x4F);
					zombies_restantes_A--;
					print(dame_numero(zombies_restantes_A), 27, 47, 0x4F);
				}
			}
			break;
		case 0x36: //rshift
			if (primer_pos_libre(tareas_B) != 8)	// Esto significa que hay lugar libre
			{
				unsigned int fisica_nuevo_zombie = dame_fisica(77, posicion_jugador_B);
				posicion_zombie_B_F[primer_pos_libre(tareas_B)] = posicion_jugador_B;
				posicion_zombie_B_C[primer_pos_libre(tareas_B)] = 77;
				clase_zombie_B[primer_pos_libre(tareas_B)] = tipo_zombie_B;
				unsigned int cr3 = (unsigned int)mmu_inicializar_dir_zombie();
				cr3_B[primer_pos_libre(tareas_B)] = cr3;
				mmu_mappear_pagina(0x8000000, cr3, fisica_nuevo_zombie, 1);
				mapear_contorno_B(posicion_zombie_B_C[primer_pos_libre(tareas_B)], posicion_zombie_B_F[primer_pos_libre(tareas_B)], cr3, 1);
				unsigned int cr3_actual = rcr3();
				mmu_mappear_pagina(0x9000000, cr3_actual, fisica_nuevo_zombie, 1); //TODO: CAMBIAR ESTO
				unsigned int fisica_codigo_zombie = 0x13000 + tipo_zombie_B*0x1000;
				copiar_pagina_4k((unsigned int*)0x9000000, (unsigned int*)fisica_codigo_zombie);
				mmu_unmappear_pagina(0x9000000, cr3_actual);
				tss_inicializar_zombie(1, cr3);
				print(clase_zombie(tipo_zombie_B), 77, posicion_jugador_B, 0x1F);
				zombies_restantes_B--;
				print(dame_numero(zombies_restantes_B), 42, 47, 0x1F);
				
			}
			break;
		
		default:
			break;
	}
}

void mover_jugador(unsigned int direccion)
{
	switch (direccion)
	{
		case 0x11: // Arriba jugador_A 
			if ( posicion_jugador_A == 1)
			{
				print(" ", 0, posicion_jugador_A, 0x40);
				posicion_jugador_A = 44;
				print(clase_zombie(tipo_zombie_A), 0, posicion_jugador_A, 0x4F);
				break;
			}
			else
			{
				print(" ", 0, posicion_jugador_A, 0x40);
				posicion_jugador_A--;
				print(clase_zombie(tipo_zombie_A), 0, posicion_jugador_A, 0x4F);
				break;
			}
		case 0x1f: // Abajo jugador_A
			if ( posicion_jugador_A == 44)
			{
				print(" ", 0, posicion_jugador_A, 0x40);
				posicion_jugador_A = 1;
				print(clase_zombie(tipo_zombie_A), 0, posicion_jugador_A, 0x4F);
				break;
			}
			else
			{
				print(" ", 0, posicion_jugador_A, 0x40);
				posicion_jugador_A++;
				print(clase_zombie(tipo_zombie_A), 0, posicion_jugador_A, 0x4F);
				break;
			}
		case 0x17: // Arriba jugador_B
			if ( posicion_jugador_B == 1)
			{
				print(" ", 79, posicion_jugador_B, 0x10);
				posicion_jugador_B = 44;
				print(clase_zombie(tipo_zombie_B), 79, posicion_jugador_B, 0x1F);
				break;
			}
			else
			{
				print(" ", 79, posicion_jugador_B, 0x10);
				posicion_jugador_B--;
				print(clase_zombie(tipo_zombie_B), 79, posicion_jugador_B, 0x1F);
				break;
			}
		case 0x25: // Abajo jugador_B
			if ( posicion_jugador_B == 44)
			{
				print(" ", 79, posicion_jugador_B, 0x10);
				posicion_jugador_B = 1;
				print(clase_zombie(tipo_zombie_B), 79, posicion_jugador_B, 0x1F);
				break;
			}
			else
			{
				print(" ", 79, posicion_jugador_B, 0x10);
				posicion_jugador_B++;
				print(clase_zombie(tipo_zombie_B), 79, posicion_jugador_B, 0x1F);
				break;
			}
		default:  
			break;
	}
}

const char * clase_zombie(int t)
{
	switch (t)
	{
		case 0: // zombie_Guerrero
			return "G";
			break;
		case 1: // zombie_Mago
			return "M";
			break;
		case 2: // zombie_clerigo
			return "C";
			break;
		default:  
			break;
			return "0";
	}
	return "1";
}

const char * clase_zombie_aux(int t)
{
	switch (t)
	{
		case 0: // zombie_Guerrero
			return "Guerrero";
			break;
		case 1: // zombie_Mago
			return "Mago";
			break;
		case 2: // zombie_clerigo
			return "Clerigo";
			break;
		default:  
			break;
			return "0";
	}
	return "1";
}


unsigned int codigo_tarea(unsigned int tipo)
{
	if(jugador_actual == 0)
	{
		return 0x10000 + tipo*0x1000;
	}
	else
	{
		return 0x13000 + tipo*0x1000;
	}
}

void desalojar_tarea()
{
	// 1) Sacar la tarea del scheduler

	if (jugador_actual == 0)
	{	
		tareas_A[tarea_actualA] = 0;
	}
	else
	{
		tareas_B[tarea_actualB] = 0;
	}
}

void pintar_tarea()
{
	// 1) Para pintar la clase del zombie
	// Aclaro que esto es horrible pero en screen.c no me toma bien la clase del zombie para pintarla

	if (jugador_actual == 0)
	{	
		print(clase_zombie_aux(clase_zombie_A[tarea_actualA]), 35, 7, 0x1F);
	}	
	else
	{
		print(clase_zombie_aux(clase_zombie_B[tarea_actualB]), 35, 7, 0x1F);
	}
}
