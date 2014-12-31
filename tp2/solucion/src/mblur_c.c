#include "tp2.h"

#define MIN(x,y) ( x < y ? x : y )
#define MAX(x,y) ( x > y ? x : y )
#define P 2

void mblur_c    (
    unsigned char *src,
    unsigned char *dst,
    int cols,
    int filas,
    int src_row_size,
    int dst_row_size)
{
    unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
    unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;
	
	for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0; columna < cols; columna++)
        {
			bgra_t *p_d = (bgra_t*)&dst_matrix[fila][columna*4];
			bgra_t *p_s = (bgra_t*)&src_matrix[fila][columna*4];
			if(fila < 2 || columna < 2 || fila+2 > filas - 1 || columna+2 > cols - 1)
			{
				p_d->b = 0;
				p_d->g = 0;
				p_d->r = 0;
			}
			else
			{
				unsigned int blue = 0;
				unsigned int green = 0;
				unsigned int red = 0;
				
				for (int offset = -2; offset < 3; offset++)
				{
					bgra_t *p_p = (bgra_t*) &src_matrix[fila+offset][(columna+offset) * 4];
					blue += p_p->b;
					green += p_p->g;
					red += p_p->r;
				}
				blue = (int) blue*0.2;
				green = (int) green*0.2;
				red = (int) red*0.2;

				p_d->b = MIN(blue, 255);
				p_d->g = MIN(green, 255);
				p_d->r = MIN(red, 255);
			}
        }
    }
}


