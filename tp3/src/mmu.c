/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

mmu_entry* page_dir = (mmu_entry*) 0x27000;
mmu_entry* page_libre = (mmu_entry*) 0x100000;

void mmu_inicializar()
{
	mmu_inicializar_dir_kernel();
}

void mmu_inicializar_dir_kernel() 
{
	// Page Directory for (inicializo todas las entradas como NO presentes)
	unsigned int i;
	for (i = 0; i < 1024; ++i)
	{
		page_dir[i].p = 0;
	}

	mmu_entry* page_table = (mmu_entry*) 0x28000;
	// Page Directory for (inicializo la tabla que voy a usar)
	
	for (i = 0; i < 1; ++i)
	{
		set_mmu_entry(page_dir, i, 1, ((int) page_table) >> 12, 1, 0);
	}

	// Page Table for (inicializo todas las entradas para direccionar los 4mb)
	for (i = 0; i < 1024; ++i)
	{
		set_mmu_entry(page_table, i, 1, i, 1, 0);
	}
}

mmu_entry* mmu_inicializar_dir_zombie()
{
	// Page Directory for (inicializo todas las entradas como NO presentes)
	mmu_entry* pd = area_libre_mmu();
	mmu_entry* res = pd;
	unsigned int i;
	for (i = 0; i < 1024; ++i)
	{
		pd[i].p = 0;
	}

	mmu_entry* pt = area_libre_mmu();
	// Page Directory for (inicializo la tabla que voy a usar)
	
	for (i = 0; i < 1; ++i)
	{
		set_mmu_entry(pd, i, 1, ((int) pt) >> 12, 1, 0);
	}

	// Page Table for (inicializo todas las entradas para direccionar los 4mb)
	for (i = 0; i < 1024; ++i)
	{
		set_mmu_entry(pt, i, 1, i, 1, 0);
	}
	return res;
}

void mmu_mappear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char attrs)
{	
	unsigned int cr3_Aux = cr3 >> 12;
	cr3_Aux = cr3_Aux << 12;
	mmu_entry* pd_zombie = (mmu_entry*) cr3_Aux; // VOY AL PD DEL ZOMBIE
	unsigned int offset_pd = virtual >> 22; // GUARDO EL OFFSET DEL PD
	pd_zombie = pd_zombie + offset_pd; // VOY AL PAGE_TABLE CORRESPONDIENTE DEL PD DEL ZOMBIE

	if(pd_zombie->p == 0) //SI NO ESTA PRESENTE LA PT SE PIDE MEMORIA Y SE CREA UNA NUEVA
	{
		pd_zombie->p = 1;
		pd_zombie->rw = 1;
		pd_zombie->us = attrs;
		pd_zombie->pwt = 0;
		pd_zombie->pcd = 0;
		pd_zombie->a = 0;
		pd_zombie->ign = 0;
		pd_zombie->ps = 0;
		pd_zombie->g = 0;
		pd_zombie->disp = 0;
		pd_zombie->base_0_20 = ((int) area_libre_mmu()) >> 12; // LA FUNCION AREA_LIBRE() PIDE MEMORIA PARA CREAR LA PAGE_TABLE
	}
	unsigned int pt_Aux = pd_zombie->base_0_20 << 12; 
	mmu_entry* pt_zombie = (mmu_entry*) pt_Aux ; //VOY A LA PAGE_TABLE
	unsigned int offset_pt = virtual << 10;
	offset_pt = offset_pt >> 22; //TENGO EL OFFSET DE LA PAGE_TABLE
	pt_zombie = pt_zombie + offset_pt; //VOY AL OFFSET CORRESPONDIENTE DE LA PAGE_TABLE
	pt_zombie->p = 1;
	pt_zombie->rw = 1;
	pt_zombie->us = attrs;
	pt_zombie->pwt = 0;
	pt_zombie->pcd = 0;
	pt_zombie->a = 0;
	pt_zombie->ign = 0;
	pt_zombie->ps = 0;
	pt_zombie->g = 0;
	pt_zombie->disp = 0;
	pt_zombie->base_0_20 = fisica >> 12; // LA FUNCION AREA_LIBRE() PIDE MEMORIA PARA CREAR LA PAGE_TABLE
	
	tlbflush();
}

void mmu_unmappear_pagina(unsigned int virtual, unsigned int cr3)
{
	unsigned int cr3_Aux = cr3 >> 12;
	cr3_Aux = cr3_Aux << 12;
	mmu_entry* pd_zombie = (mmu_entry*) cr3_Aux; // VOY AL PD DEL ZOMBIE
	unsigned int offset_pd = virtual >> 22; // GUARDO EL OFFSET DEL PD
	pd_zombie = pd_zombie + offset_pd; // VOY AL PAGE_TABLE CORRESPONDIENTE DEL PD DEL ZOMBIE

	unsigned int pt_Aux = pd_zombie->base_0_20 << 12; 
	mmu_entry* pt_zombie = (mmu_entry*) pt_Aux ; //VOY A LA PAGE_TABLE
	unsigned int offset_pt = virtual << 10;
	offset_pt = offset_pt >> 22; //TENGO EL OFFSET DE LA PAGE_TABLE
	pt_zombie = pt_zombie + offset_pt; //VOY AL OFFSET CORRESPONDIENTE DE LA PAGE_TABLE
	pt_zombie->p = 0;
	
	tlbflush();
}

mmu_entry* area_libre_mmu()
{
	mmu_entry* res = page_libre;
	page_libre += 0x1000 ;
	return res;
}


void set_mmu_entry(mmu_entry* mmuentry, unsigned int j, unsigned char p1, unsigned int base_0_201, 
					unsigned char rw1, unsigned char us1)
{
		mmuentry[j].p = p1;
		mmuentry[j].base_0_20 = base_0_201;
		mmuentry[j].rw = rw1;
		mmuentry[j].us = us1;
		mmuentry[j].pwt = 0x0;
		mmuentry[j].pcd = 0x0;
		mmuentry[j].a = 0x0;
		mmuentry[j].ign = 0x0;
		mmuentry[j].ps = 0x0;
		mmuentry[j].g = 0x0;
		mmuentry[j].disp = 0x0;
}

void copiar_pagina_4k(unsigned int* dst, unsigned int* src)
{
	int i;
	//breakpoint();
	for (i = 0; i < 1024; ++i)
	{
		dst[i] = src[i];
	}
}

int primer_pos_libre(int* tareas) // Devuelve la primer posicion libre del vector
{
	int i;
	for( i = 0; i < 8; i++)
	{
		if( tareas[i] == 0)
		{
			return i;
		} 
	} 
	return 8;
}

unsigned int dame_fisica(int c, int f)
{
	return 0x400000 + (c*0x1000) + (f*0x1000* SIZE_W);
}
