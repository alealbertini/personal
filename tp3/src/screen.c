/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "screen.h"
#include "i386.h"
extern const char * clase_zombie(int t);
extern const char * clase_zombie_aux(int t);
extern int tipo_zombie_A;
extern int tipo_zombie_B;
extern int jugador_actual;
unsigned char matriz_aux[VIDEO_FILS*VIDEO_COLS*2];
extern unsigned int puntos_jugador_A;
extern unsigned int puntos_jugador_B;
extern unsigned int zombies_restantes_A;
extern unsigned int zombies_restantes_B;
extern int* tareas_A;
extern int* tareas_B;
extern char* modo_debug;
extern int tarea_actualA;
extern int tarea_actualB;
extern int* clase_zombie_A;
extern int* clase_zombie_B;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void pintarTablero(){

	memoria_video* vd = (memoria_video*) (0xb8000);

	
	int f;
	int c;
	for ( f = 0; f < VIDEO_FILS; f++ )
	{
		for ( c = 0; c < VIDEO_COLS ; c++)
		{
			vd->ascii = 0x0;
			vd->caracter = 0x0;
			vd->brillante = 0x0;
			vd->fondo = 0x0;
			vd->blink = 0x0; 		
			if( f == 0 )
			{	
				vd->fondo = C_FG_BLACK;
				vd++;
			}
			if( f > 0 && f < 45)
			{
				if( c == 0)
				{
					vd->fondo = C_FG_RED;
					vd++;
				}
				else
				{
					if( c == 79)
					{
						vd->fondo = C_FG_BLUE;
						vd++;
					}	
					else
					{
						vd->fondo = C_FG_GREEN;
						vd++;
					}
				}
			}
			if( f > 44)
			{
				if( c > 30 && c < 36)
				{
					vd->fondo = C_FG_RED;
					vd++;
				}
				else
				{
					if( c > 35 && c < 41)
					{
						vd->fondo = C_FG_BLUE;
						vd++;
					}
					else
					{
						vd->fondo = C_FG_BLACK;
						vd++;
					}
				}
			}
			
		}
	}
	print("1", 5, 46, 0x0F);
	print("2", 7, 46, 0x0F);
	print("3", 9, 46, 0x0F);
	print("4", 11, 46, 0x0F);
	print("5", 13, 46, 0x0F);
	print("6", 15, 46, 0x0F);         
	print("7", 17, 46, 0x0F);
	print("8", 19, 46, 0x0F);
	print("1", 60, 46, 0x0F);
	print("2", 62, 46, 0x0F);
	print("3", 64, 46, 0x0F);
	print("4", 66, 46, 0x0F);
	print("5", 68, 46, 0x0F);
	print("6", 70, 46, 0x0F);         
	print("7", 72, 46, 0x0F);
	print("8", 74, 46, 0x0F);
	
	print("_", 5, 48, 0x0F);
	print("_", 7, 48, 0x0F);
	print("_", 9, 48, 0x0F);
	print("_", 11, 48, 0x0F);
	print("_", 13, 48, 0x0F);
	print("_", 15, 48, 0x0F);         
	print("_", 17, 48, 0x0F);
	print("_", 19, 48, 0x0F);
	print("_", 60, 48, 0x0F);
	print("_", 62, 48, 0x0F);
	print("_", 64, 48, 0x0F);
	print("_", 66, 48, 0x0F);
	print("_", 68, 48, 0x0F);
	print("_", 70, 48, 0x0F);         
	print("_", 72, 48, 0x0F);
	print("_", 74, 48, 0x0F);
	
  print(clase_zombie(tipo_zombie_A), 0, 1, 0x4F);
  
    print(dame_numero(zombies_restantes_A), 27, 47, 0x4F);
    print(dame_numero(puntos_jugador_A), 33, 47, 0x4F);
  
    print(dame_numero(puntos_jugador_B), 38, 47, 0x4F);
    print(dame_numero(zombies_restantes_B), 42, 47, 0x4F);
  
    print("Debug: NO", 47, 47, 0x0F);

    print(clase_zombie(tipo_zombie_B), 79, 1, 0x1F);
}

void mostrar_int(int error){

	switch ( error)
	{
		case 0:
			print("Divide Error Exception (#DE)", 0, 0, 0xAF);   
			break;
		case 1:
			print("Debug Exception (#DB)", 0, 0,0xAF);
			break;
		case 2:
			print("NMI Interrupt", 0, 0,0xAF);
			break;
		case 3:
			print("Breakpoint Exception (#BP)", 0, 0,0xAF);
			break;
		case 4:
			print("Overflow Exception (#OF)", 0, 0,0xAF);
			break;
		case 5:
			print("BOUND Range Exceeded Exception (#BR)", 0, 0,0xAF);
			break;
		case 6:
			print("Invalid Opcode Exception (#UD)", 0, 0,0xAF);
			break;
		case 7:
			print("Device Not Available Exception (#NM)", 0, 0,0xAF);
			break;
		case 8:
			print("Double Fault Exception (#DF)", 0, 0,0xAF);
			break;
		case 9:
			print("Coprocessor Segment Overrun", 0, 0,0xAF);
			break;
		case 10:
			print("Invalid TSS Exception (#TS)", 0, 0,0xAF);
			break;
		case 11:
			print("Segment Not Present (#NP)", 0, 0,0xAF);
			break;
		case 12:
			print("Stack Fault Exception (#SS)", 0, 0,0xAF);
			break;
		case 13:
			print("General Protection Exception (#GP)", 0, 0,0xAF);
			break;
		case 14:
			print("Page-Fault Exception (#PF)", 0, 0,0xAF);
			break;
		case 15:
			print("", 0, 0,0xAF);
			break;
		case 16:
			print("x87 FPU Floating-Point Error (#MF)", 0, 0,0xAF);
			break;
		case 17:
			print("Alignment Check Exception (#AC)", 0, 0,0xAF);
			break;
		case 18:
			print("Machine-Check Exception (#MC)", 0, 0,0xAF);
			break;
		case 19:
			print("SIMD Floating-Point Exception (#XM)", 0, 0,0xAF);
			break;
	}
}


void print_keyboar_int(unsigned int scanCode){

	switch (scanCode)
	{
		case 0xff11: //w
			print("W", 79, 0, 0xf);   
			break;
		case 0xff1e: //a
			print("A", 79, 0, 0xf);   
			break;
		case 0xff1f: //s
			print("S", 79, 0, 0xf);   
			break;
		case 0xff20: //d
			print("D", 79, 0, 0xf);   
			break;
		case 0xff2a: //lshift
			print("LS", 78, 0, 0xf);   
			break;
		case 0xff17: //i
			print("I", 79, 0, 0xf);   
			break;
		case 0xff24: //j
			print("J", 79, 0, 0xf);   
			break;
		case 0xff25: //k
			print("K", 79, 0, 0xf);   
			break;
		case 0xff26: //l
			print("L", 79, 0, 0xf);   
			break;
		case 0xff36: //rshift
			print("RS", 78, 0, 0xf);   
			break;
		default:
			//print("NO ES UNA TECLA VALIDA", 0, 0, 0xf);   
			break;
	}
}


void memcopy(unsigned char* source, unsigned char* dst, int tam){
    int i;
    for(i=0; i<tam; i++){
	*dst = *source;
	dst++;
	source++;
    }
}

void guardar_pantalla(){	

	unsigned char* vd = (unsigned char*) (0xb8000);
	
	memcopy((unsigned char*)vd, matriz_aux, 80*50*2);
	
}





void restablecer_pantalla(){	

	unsigned char* vd = (unsigned char*) 0xb8000;
	
	memcopy(matriz_aux, (unsigned char*)vd, 80*50*2);
}



void pantalla_negra(){	

	memoria_video* vd = (memoria_video*) (0xb8000);
	
	int f;
	int c;
	for ( f = 0; f < VIDEO_FILS; f++ )
	{
		for ( c = 0; c < VIDEO_COLS ; c++)
		{
			vd->ascii = 0x0;
			vd->caracter = 0x0;
			vd->brillante = 0x0;
			vd->fondo = 0x0;
			vd->blink = 0x0;
			vd++;
			
		}
	}
	
	//breakpoint();
}



void pintarDebugger(unsigned int eax,
		    unsigned int ebx,
		    unsigned int ecx,
		    unsigned int edx,
		    unsigned int esi,
		    unsigned int edi,
		    unsigned int ebp,
		    unsigned int esp,
		    unsigned int eip,
		    unsigned int cs,
		    unsigned int ds,
		    unsigned int es,
		    unsigned int fs,
		    unsigned int gs,
		    unsigned int ss, 
	            unsigned int eflags, unsigned int s5, unsigned int s4, unsigned int s3, unsigned int s2, unsigned int s1
		    ){

	memoria_video* vd = (memoria_video*) (0xb8000);

	
	int f;
	int c;
	for ( f = 0; f < VIDEO_FILS; f++ )
	{
		for ( c = 0; c < VIDEO_COLS ; c++)
		{	
		      if( f >= 6 && f <= 43 ){
			    
			    if( c >= 25 && c <= 54 ){
				  
				  if( f == 6 || f == 43 || c == 25 || c == 54){
				      print(" ", c, f, 0x77);
				      vd->fondo = C_FG_BLACK;
				      vd++;
				  }else if( f == 7  && (c >= 26 && c <= 53)){
				      print(" ", c, f, 0x77);
				      vd->fondo = C_FG_BLUE;
				      vd++;
				  }else{
					  print(" ", c, f, 0x77);
				      vd->fondo = C_FG_LIGHT_GREY;
				      vd++;
				  }

			    }else{
			      vd++;
			    }
		      }else{
			vd++;
		      }
		      
		}	

	}
	
	
	print("eax", 27, 10, 0x70);
	print("ebx", 27, 12, 0x70);
	print("ecx", 27, 14, 0x70);
	print("edx", 27, 16, 0x70);
	print("esi", 27, 18, 0x70);
	print("edi", 27, 20, 0x70);         
	print("ebp", 27, 22, 0x70);
	print("esp", 27, 24, 0x70);
	print("eip", 27, 26, 0x70);
	print("cs", 28, 28, 0x70);
	print("ds", 28, 30, 0x70);
	print("es", 28, 32, 0x70);
	print("fs", 28, 34, 0x70);
	print("gs", 28, 36, 0x70);         
	print("ss", 28, 38, 0x70);
	print("eflags", 28, 40, 0x70);
	print("cr0", 41, 10, 0x70);
	print("cr2", 41, 12, 0x70);
	print("cr3", 41, 14, 0x70);
	print("cr4", 41, 16, 0x70);
	print("stack", 41, 27, 0x70);
	print("Zombi", 26, 7, 0x1F);
	

	
	print_hex(eax, 8, 31, 10, 0x7F);
	print_hex(ebx, 8, 31, 12, 0x7F);
	print_hex(ecx, 8, 31, 14, 0x7F);
	print_hex(edx, 8, 31, 16, 0x7F);
	print_hex(esi, 8, 31, 18, 0x7F);
	print_hex(edi, 8, 31, 20, 0x7F);         
	print_hex(ebp, 8, 31, 22, 0x7F);
	print_hex(esp, 8, 31, 24, 0x7F);
	print_hex(eip, 8, 31, 26, 0x7F);
	print_hex(cs, 4, 31, 28, 0x7F);
	print_hex(ds, 4, 31, 30, 0x7F);
	print_hex(es, 4, 31, 32, 0x7F);
	print_hex(fs, 4, 31, 34, 0x7F);
	print_hex(gs, 4, 31, 36, 0x7F);         
	print_hex(ss, 4, 31, 38, 0x7F);
	print_hex(eflags, 8, 34, 40, 0x7F);
	print_hex(rcr0(), 8, 45, 10, 0x7F);
	print_hex(rcr2(), 8, 45, 12, 0x7F);
	print_hex(rcr3(), 8, 45, 14, 0x7F);
	print_hex(rcr4(), 8, 45, 16, 0x7F);
	
	print_hex(s1, 8, 41, 29, 0x7F);
	print_hex(s2, 8, 41, 30, 0x7F);
	print_hex(s3, 8, 41, 31, 0x7F);
	print_hex(s4, 8, 41, 32, 0x7F);
	print_hex(s5, 8, 41, 33, 0x7F);
	
	
	if(jugador_actual == 0){
		print("B", 32, 7, 0x1F);		      // jugador B
	//	print(clase_zombie_aux(clase_zombie_A[tarea_actualA]), 35, 7, 0x1F);
			  
	}else{
		print("A", 32, 7, 0x1F);		      // jugador A
	//	print(clase_zombie_aux(clase_zombie_A[tarea_actualA]), 35, 7, 0x1F);
	}
	
}

const char * dame_numero(int n)
{
	switch(n)
	{
		case 0:
			return "0";
			break;
		case 1:
			return "1";
			break;
		case 2:
			return "2";
			break;
		case 3:
			return "3";
			break;
		case 4:
			return "4";
			break;
		case 5:
			return "5";
			break;
		case 6:
			return "6";
			break;
		case 7:
			return "7";
			break;
		case 8:
			return "8";
			break;
		case 9:
			return "9";
			break;
		case 10:
			return "10";
			break;
		case 11:
			return "11";
			break;
		case 12:
			return "12";
			break;
		case 13:
			return "13";
			break;
		case 14:
			return "14";
			break;
		case 15:
			return "15";
			break;
		case 16:
			return "16";
			break;
		case 17:
			return "17";
			break;
		case 18:
			return "18";
			break;
		case 19:
			return "19";
			break;
		case 20:
			return "20";
			break;
	}
	return "1";	
}

void print_debug_mode(int i)
{
    if (i == 0)
    {
        print("Debug: NO", 47, 47, 0x0F);
    }
    else
    {
        print("Debug: SI", 47, 47, 0x0F);
    }
}
