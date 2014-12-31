
#include "tp2.h"


void cropflip_c    (
	unsigned char *src,
	unsigned char *dst,
	int cols,
	int filas,
	int src_row_size,
	int dst_row_size,
	int tamx,
	int tamy,
	int offsetx,
	int offsety)
{
	unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
	unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;

	for (int i = 0; i < tamy; i++) {
		for (int j = 0; j < tamx; j++) {
			
			bgr_t *p_d = (bgr_t*)&dst_matrix[i][j*4];
			bgr_t *p_s = (bgr_t*)&src_matrix[tamy+offsety-i-1][offsetx*4+j*4];
			*p_d = *p_s;
			
			
			}}	
}
