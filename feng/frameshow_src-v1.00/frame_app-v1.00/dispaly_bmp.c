#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_BMP
/* display bitmap */
void display_bmp(const fb_info fb_inf, const char *bmpname)
{
    int fd;
//    unsigned char rd_rgb[3];
    int rgb;
    int iloop;
    int jloop;
    int bmpwidth;
    int bmpheight;
  
    if ((fd = open(bmpname, O_RDONLY)) < 0)
    {
        fprintf(stderr, "Open %s failed:%s\n", bmpname, strerror(errno));
        exit(1);
    }

    if (lseek(fd, 18, SEEK_SET) < 0)
    {
        perror("lseek 18");
        exit(1);
    }

    if (read(fd, &bmpwidth, 4) < 0)
    {
        perror("read bmpwidth");
        exit(1);
    }
    if (read(fd, &bmpheight, 4) < 0)
    {
        perror("read bmpwidth");
        exit(1);
    }    

    if (lseek(fd, 54, SEEK_SET) < 0)
    {
        perror("lseek 54");
        exit(1);
    }

    for (jloop = bmpheight - 1; jloop >= 0; jloop--)
    {
       for (iloop = 0; iloop < bmpwidth; iloop++)
        {
           rgb = 0;
//           if (read(fd, rd_rgb, 3) < 0)
           if (read(fd, &rgb, 3) < 0)
            {
               perror("read rgb");
               exit(1);
            } 
//           rgb = rgb + rd_rgb[2];
//           rgb = (rgb << 8) + rd_rgb[1];
//           rgb = (rgb << 8)+ rd_rgb[0];
//            rgb = rgb << 8;

           fb_pixel(fb_inf, iloop, jloop, rgb);
        }        
    }

    close(fd);
}
#endif

