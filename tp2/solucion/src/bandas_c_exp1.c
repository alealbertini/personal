#include "tp2.h"

/*void bandas(bgr_t* p_d, unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int suma = (r + g + b);
	
		if 	(suma < 96)		{p_d->b = 0; 	p_d->g = 0; 	p_d->r = 0;}
	else if (suma < 288)	{p_d->b = 64; 	p_d->g = 64; 	p_d->r = 64;}
	else if (suma < 480)	{p_d->b = 128;	p_d->g = 128; 	p_d->r = 128;}
	else if (suma < 672)	{p_d->b = 192; 	p_d->g = 192;	p_d->r = 192;}
	else 					{p_d->b = 255;	p_d->g = 255; 	p_d->r = 255;}
}*/

void bandas_c (
	unsigned char *src,
	unsigned char *dst,
	int cols,
	int filas,
	int src_row_size,
	int dst_row_size
) 
{
	unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
	unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;

	for (int i = 0; i < filas; i++) 
	{
		for (int j = 0; j < cols; j++) 
		{
			bgr_t *p_d = (bgr_t*)&dst_matrix[i][j*4];
			bgr_t *p_s = (bgr_t*)&src_matrix[i][j*4];
			p_d->b = 128;	
			p_d->g = 128; 	
			p_d->r = 128;
		}
	}	
}
