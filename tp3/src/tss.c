/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle;
int tareas_A[CANT_ZOMBIS];
int tareas_B[CANT_ZOMBIS];
tss tss_zombisA[CANT_ZOMBIS];
tss tss_zombisB[CANT_ZOMBIS];
extern mmu_entry* page_libre;

void tss_inicializar() 
{
	// Completo la base de la tss_inicial en la gdt
	unsigned int base =  (unsigned int) &tss_inicial;
	base  = (base << 16) >> 16;
	gdt[GDT_IDX_TSS_INICIAL].base_0_15 = (unsigned short) base;
	base = (((unsigned int)&tss_inicial) << 8) >> 24;
	gdt[GDT_IDX_TSS_INICIAL].base_23_16 = (unsigned short) base;
	base = ((unsigned int)&tss_inicial) >> 24;
	gdt[GDT_IDX_TSS_INICIAL].base_31_24 = (unsigned short) base;

	// Completo la base de la tss_idle en la gdt
	base =  (unsigned int) &tss_idle;
	base  = (base << 16) >> 16;
	gdt[GDT_IDX_TSS_IDLE].base_0_15 = (unsigned short) base;
	base = (((unsigned int)&tss_idle) << 8) >> 24;
	gdt[GDT_IDX_TSS_IDLE].base_23_16 = (unsigned short) base;
	base = ((unsigned int)&tss_idle) >> 24;
	gdt[GDT_IDX_TSS_IDLE].base_31_24 = (unsigned short) base;
	
	// Completo el eip de la tss_idle en la gdt
	tss_idle.eip = 0x16000;
	tss_idle.ebp = 0x27000;
	tss_idle.esp = tss_idle.ebp;
	tss_idle.cr3 = 0x27000; //TODO: preguntar
	tss_idle.ds = 0x50;
	tss_idle.es = 0x50;
	tss_idle.gs = 0x50;
	tss_idle.ss = 0x50;
	tss_idle.cs = 0x40;
	tss_idle.eflags = 0x202;
	int i;
	for( i = 0; i < 8; i++)
	{
		unsigned int base =  (unsigned int) &tss_zombisA[i];
		base  = (base << 16) >> 16;
		gdt[i+15].base_0_15 = (unsigned short) base;
		base = (((unsigned int)&tss_zombisA[i]) << 8) >> 24;
		gdt[i+15].base_23_16 = (unsigned short) base;
		base = ((unsigned int)&tss_zombisA[i]) >> 24;
		gdt[i+15].base_31_24 = (unsigned short) base;
		
		base =  (unsigned int) &tss_zombisB[i];
		base  = (base << 16) >> 16;
		gdt[i+23].base_0_15 = (unsigned short) base;
		base = (((unsigned int)&tss_zombisB[i]) << 8) >> 24;
		gdt[i+23].base_23_16 = (unsigned short) base;
		base = ((unsigned int)&tss_zombisB[i]) >> 24;
		gdt[i+23].base_31_24 = (unsigned short) base;
		
		tareas_A[i] = 0;
		tareas_B[i] = 0;
	}
}

unsigned int area_libre_tss()
{
	unsigned int res = (unsigned int)page_libre;
	page_libre += 0x1000;
	return res;
}


void tss_inicializar_zombie(int jugador, unsigned int cr3) // jugador 0 = jugador A
{
	// Completo la base de la tss_zombie en la gdt
	//int primer_libre; // TODO: sacar esto
	if (jugador == 0)
	{
		int primer_libre = primer_pos_libre(tareas_A);
		set_tss_entry(	&tss_zombisA[primer_libre],
						area_libre_tss() + 0x1000,
						cr3);
		tareas_A[primer_libre] = 1;
	}
	else
	{
		int primer_libre = primer_pos_libre(tareas_B);
		set_tss_entry(	&tss_zombisB[primer_libre],
						area_libre_tss() + 0x1000,
						cr3);
		tareas_B[primer_libre] = 1;
	}
}

void set_tss_entry(	tss* tss_entry,
					unsigned int esp0,
					unsigned int cr3)
{
    tss_entry->ptl = 0x0;
    tss_entry->unused0 = 0x0;
    tss_entry->esp0 = esp0;
    tss_entry->ss0 = (unsigned short) GDT_IDX_DATOS_KERNEL*8;
    tss_entry->unused1 = 0x0;
    tss_entry->esp1 = 0x0;
    tss_entry->ss1 = 0x0;
    tss_entry->unused2 = 0x0;
    tss_entry->esp2 = 0x0;
    tss_entry->ss2 = 0x0;
    tss_entry->unused3 = 0x0;
    tss_entry->cr3 = cr3;
    tss_entry->eip = 0x08000000;
    tss_entry->eflags = 0x202;
    tss_entry->eax = 0x0;
    tss_entry->ecx = 0x0;
    tss_entry->edx = 0x0;
    tss_entry->ebx = 0x0;
    tss_entry->esp = 0x08001000;
    tss_entry->ebp = 0x08001000;
    tss_entry->esi = 0x0;
    tss_entry->edi = 0x0;
    tss_entry->es = (unsigned short) GDT_IDX_DATOS_USUARIO*8 + 3;
    tss_entry->unused4 = 0x0;
    tss_entry->cs = (unsigned short) GDT_IDX_CODIGO_USUARIO*8 + 3;
    tss_entry->unused5 = 0x0;
    tss_entry->ss = (unsigned short) GDT_IDX_DATOS_USUARIO*8 + 3;
    tss_entry->unused6 = 0x0;
    tss_entry->ds = (unsigned short) GDT_IDX_DATOS_USUARIO*8 + 3;
    tss_entry->unused7 = 0x0;
    tss_entry->fs = (unsigned short) GDT_IDX_DATOS_USUARIO*8 + 3;
    tss_entry->unused8 = 0x0;
    tss_entry->gs = (unsigned short) GDT_IDX_DATOS_USUARIO*8 + 3;
    tss_entry->unused9 = 0x0;
    tss_entry->ldt = 0x0;
    tss_entry->unused10 = 0x0;
    tss_entry->dtrap = 0X0;	//preguntar
    tss_entry->iomap = 0X0;	//preguntar
}

void zombie_en_uso()
{
	int i;
	for( i = 0; i < 8; i++)
	{
		if(tareas_A[i] == 0)
		{
			print("_", 5 + (2*i), 48, 0x0F);
		}
		else
		{
			print("X", 5 + (2*i), 48, 0x4F);
		}
	}
	for( i = 0; i < 8; i++)
	{
		if(tareas_B[i] == 0)
		{
			print("_", 60 + (2*i), 48, 0x0F);
		}
		else
		{
			print("X", 60 + (2*i), 48, 0x1F);
		}
	}
}
