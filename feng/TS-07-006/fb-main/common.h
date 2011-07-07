/* common.h */
#ifndef __COMMON_H__
#define __COMMON_H__

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

typedef struct 
{
	int w;				  /* width */
	int h;				  /* high */
	int bpp;				  /* bits per pixel */
	u8_t *fbmem;
}fb_info;

/* ******************** fb.c ******************** */

/* initial framebuf */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);

/* painting horizontal */
int fb_pixel_row(fb_info fb_inf, int x, int y, int len, u32_t color);

/* Framebuffer Test */
int fb_test(void);

/* draw a triangle */
int fb_draw_triangle(const fb_info fb_inf, int x, int y, int len, u32_t color);
/* draw a color ball */
int fb_draw_ball(const fb_info fb_inf, int x, int y, int len, u32_t color);

/* draw a color squarearea */
int fb_draw_squarearea(const fb_info fb_inf, int x, int y, int x_len, int y_len, u32_t color);

#endif    /* __COMMON_H__ */

