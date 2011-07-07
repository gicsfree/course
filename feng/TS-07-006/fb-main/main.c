/* main.c */
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/* main function */
int main(int argc, char *argv[]) 
{
       fb_info fb_inf;
	if (init_fb(&fb_inf) < 0)
        {
		fprintf(stderr, "Error initial framebuffer\b")	;
		return 1;
	}
        
	/* point test */
	fb_pixel(fb_inf, 640, 400, 0xFFFFFFFF);
	/* line test */
	fb_pixel_row(fb_inf, 0, 200, 1280, 0xFF0000);

       /* draw a color squarearea */
	fb_draw_squarearea(fb_inf, 0, 0, fb_inf.w, fb_inf.h, 0xFF0000);

	fb_draw_triangle(fb_inf, 200, 220, 150, 0x00FFFF00);

	fb_draw_triangle(fb_inf, 380, 70, 40, 0x00FFFF00);	
	fb_draw_triangle(fb_inf, 440, 170, 40, 0x00FFFF00);
	fb_draw_triangle(fb_inf, 430, 270, 40, 0x00FFFF00);
	fb_draw_triangle(fb_inf, 380, 370, 40, 0x00FFFF00);
         
	munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);

	return 0;
}

