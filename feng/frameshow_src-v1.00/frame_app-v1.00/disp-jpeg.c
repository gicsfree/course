/* disp-jpeg.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_JPEG
////////////////////////////////////////////////////////////////
/*
* display jpeg
*/
int display_jpeg(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    
    for(xres = 0; xres < fb_inf.h; ++xres)
    {
        for (yres = 0; yres < fb_inf.w; ++yres)
        {
    		    fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * fb_inf.w)]);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

#endif    /* FRAME_SUPPORT_JPEG */
