/* draw.c */
#include <unistd.h>
#include <math.h>
#include <stdio.h>

#include "frame.h"

/* draw a color line, the slope is single */
int fb_draw_row(const fb_info fb_inf, int x, int y, int len, u32_t color)
{
    int iloop;
       
    for (iloop = 0; iloop < len; iloop++)
     {
        fb_pixel(fb_inf, x + iloop, y, color);
     }
     
    return 0;
}

/* draw a color slash line, the slope is change */
int fb_draw_slash_row(const fb_info fb_inf, int x, int y, int len, int slope, u32_t color)
{
    int iloop;
       
    for (iloop = 0; iloop < len; iloop++)
     {
        fb_pixel(fb_inf, x + iloop, y + slope * iloop, color);
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

/* draw a empty square */
int fb_draw_empty_square(const fb_info fb_inf, int x, int y, int x_len, int y_len, int s_width, u32_t color)
{
    int iloop;
    int jloop;

    for (jloop = 0; jloop < y_len + s_width; jloop++)
     {
        for (iloop = 0; iloop < x_len + s_width; iloop++)
	 {
	     if ((iloop <= s_width) || ((iloop >= x_len) && (iloop <= x_len + s_width))
	         || (jloop <= s_width) || ((jloop >= y_len) && (jloop <= y_len + s_width)))
            fb_pixel(fb_inf, x + iloop, y + jloop, color);
	 }
     }
    return 0;
}

/* draw a color circle */
int fb_draw_circle(const fb_info fb_inf, int x, int y, int len, u32_t color)
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

/* draw a color empty circle */
int fb_draw_empty_circle(const fb_info fb_inf, int x, int y, int len, int c_width, u32_t color)
{
	int i, j;
	for (i = x - len - c_width; i <= x + len + c_width; i++)

		for (j = y - len - c_width; j <= y + len + c_width; j++)
		{
			if (((i - x) * (i - x) + (j - y) * (j - y) >= len * len)
			    &&((i - x) * (i - x) + (j - y) * (j - y) <= (len + c_width) * (len + c_width)))
				fb_pixel(fb_inf, i, j, color);
		}
	return 0;
}

/* draw a color oval circle */
int fb_draw_oval_circle(const fb_info fb_inf, int x, int y, int a_len, int b_len, u32_t color)
{
	int i, j;
	for (i = x - a_len; i <= x + a_len; i++)

		for (j = y - b_len; j <= y + b_len; j++)
		{
			if (b_len * b_len * (i - x) * (i - x) + a_len * a_len * (j - y) * (j - y) 
				<= a_len * a_len * b_len * b_len)
				fb_pixel(fb_inf, i, j, color);
		}
	return 0;
}

/* draw a color empty oval circle */
int fb_draw_empty_oval_circle(const fb_info fb_inf, int x, int y, int a_len, int b_len, int c_width, u32_t color)
{
	int i, j;
	for (i = x - a_len - c_width; i <= x + a_len + c_width; i++)

		for (j = y - b_len - c_width; j <= y + b_len + c_width; j++)
		{
			if ((b_len * b_len * (i - x) * (i - x) + a_len * a_len * (j - y) * (j - y) >= a_len * a_len * b_len * b_len) 
			   && ((b_len + c_width) * (b_len + c_width) * (i - x) * (i - x) + (a_len + c_width) * (a_len + c_width) * (j - y) * (j - y) <= (a_len + c_width) * (a_len + c_width) * (b_len + c_width) * (b_len + c_width)))
				fb_pixel(fb_inf, i, j, color);
		}
	return 0;
}


