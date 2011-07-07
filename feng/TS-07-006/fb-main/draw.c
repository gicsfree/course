/* draw.c */
#include <unistd.h>
#include <math.h>
#include <stdio.h>

#include "common.h"

/*
 * draw a color line, the slope is single 
 */
int fb_draw_row(const fb_info fb_inf, int x, int y, int len, u32_t color)
{
    int iloop;
       
    for (iloop = 0; iloop < len; iloop++)
     {
        fb_pixel(fb_inf, x + iloop, y, color);
     }
     
    return 0;
}

/* draw a color squarearea */
int fb_draw_squarearea(const fb_info fb_inf, int x, int y, int x_len, int y_len, u32_t color)
{
    int iloop;
    int jloop;

    for (jloop = 0; jloop < y_len; jloop++)
     {
        for (iloop = 0; iloop < x_len; iloop++)
	 {
            fb_pixel(fb_inf, x + iloop, y + jloop, color);
	 }
     }
    return 0;
}

/* draw a color ball */
int fb_draw_ball(const fb_info fb_inf, int x, int y, int len, u32_t color)
{
	int i, j;
	for (i = x - len; i <= x + len; i++)

		for (j = y - len; j <= y + len; j++)
		{
			if ((i - x) * (i - x) + (j - y) * (j - y) <= len * len)
				fb_pixel(fb_inf, i, j, color);
		}
	return 0;
}

/* draw a triangle */
int fb_draw_triangle(const fb_info fb_inf, int x, int y, int len, u32_t color)
{
	double x_len, y_len, x_mid, y_curf, y_curl;
	double i, j;
	double drt_a = 0.0;

	double a_0 = (0.0 + drt_a) / 360 * 2 * 3.1415927;
	double a_18_r = (18.0 - drt_a) / 360 * 2 * 3.1415927;
	double a_54_r = (54.0 + drt_a) / 360 * 2 * 3.1415927;
	double a_18_l = (18.0 + drt_a) / 360 * 2 * 3.1415927;
	double a_54_l = (54.0 - drt_a) / 360 * 2 * 3.1415927;
	double a_36 = (36.0 + drt_a) / 360 * 2 * 3.1415927;
	double a_72 = (72.0 + drt_a) / 360 * 2 * 3.1425927;
	double a_144 = (144.0 + drt_a) / 360 * 2 * 3.1415927;
	double a_108 = (108.0 + drt_a) / 360 * 2 * 3.1415927;

	x_len = cos(a_54_r) * len; y_len = sin(a_54_r) * len;
	for (i = x; i <= x + x_len; i++)
	{
		y_curf = tan(a_72) * (i - x - x_len) + y + y_len;
		y_curl = tan(a_36) * (i - x - x_len) + y + y_len;
		for (j = y_curf; j <= y_curl; j++)
			fb_pixel(fb_inf, i, j, color);
	}

	x_len = cos(a_54_l) * len; y_len = sin(a_54_l) * len;
	for (i = x - x_len; i < x; i++)
	{
		y_curf = tan(a_108) * (i - x + x_len) + y + y_len;
		y_curl = tan(a_144) * (i - x + x_len) + y + y_len;
		for (j = y_curf; j <= y_curl; j++)
			fb_pixel(fb_inf, i, j, color);
	}

	x_len = cos(a_18_l) * len; y_len = sin(a_18_l) * len;
	for (i = x - x_len; i < x; i++)
	{
		y_curf = tan(a_0) * (i - x + x_len) + y - y_len;
		y_curl = tan(a_36) * (i - x + x_len) + y - y_len;
		for (j = y_curf; j <= y_curl; j++)
			fb_pixel(fb_inf, i, j, color);
	}

	x_len = cos(a_18_r) * len; y_len = sin(a_18_r) * len;
	for (i = x; i <= x + x_len; i++)
	{
		y_curf = tan(a_0) * (i - x - x_len) + y - y_len;
		y_curl = tan(a_144) * (i - x - x_len) + y - y_len;
		for (j = y_curf; j <= y_curl; j++)
			fb_pixel(fb_inf, i, j, color);
	}

	return 0;
}
