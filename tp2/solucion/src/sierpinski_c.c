
#include "tp2.h"


void sierpinski_c    (
	unsigned char *src,
	unsigned char *dst,
	int cols,
	int filas,
	int src_row_size,
	int dst_row_size)
{
	unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
	unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;
	


	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < cols; j++) {
			
			int filasI = (int) (i*255.0)/filas; 
			int colsJ = (int) (j*255.0)/cols;
			double coef = (1/255.0)*(filasI ^ colsJ);
			
			bgra_t *p_d = (bgra_t*)&dst_matrix[i][j*4];
			bgra_t *p_s = (bgra_t*)&src_matrix[i][j*4];
			p_d->b = p_s->b*coef;
			p_d->g = p_s->g*coef;
			p_d->r = p_s->r*coef;
			double d = (double)p_s->r;
			
		}
	}


}


