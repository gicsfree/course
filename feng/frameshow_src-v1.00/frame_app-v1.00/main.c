/* main.c */
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_MOUSE
/*
* mouse test
*/
int test_mouse(fb_info fb_inf)
{
    int mfd = -1;
    u8_t buf[8];
    mouse_event_t mevent;

    int m_x = fb_inf.w / 2;
    int m_y = fb_inf.h / 2;
        
    mouse_open(NULL, &mfd);
        
    fb_draw_cursor(fb_inf, m_x, m_y);
        
    for(;;)
     {
        if (read(mfd, buf, 8) != -1)
         {
	     mouse_parse(buf,&mevent);
	     //printf("dx:%d\tdy:%d\n", mevent.x, mevent.y);
	     //printf("mx:%d\tmy:%d\n", m_x, m_y);

            //if((m_y > 8) && ((m_y < (768 - 8))))
              {
	         fb_restore_cursor(fb_inf, m_x, m_y);
              }
	     m_x += mevent.x;
	     m_y += mevent.y;
              
            //if((m_y > 8) && ((m_y < (768 - 8))))
              {
	         fb_draw_cursor(fb_inf, m_x, m_y);
              }

	     switch (mevent.button)
              {
	         case 1:
		      printf("left\n");
		    break;

		  case 2:
		      printf("right\n");
		    break;
                     
		  case 3:
		      printf("middle\n");
		    break;

		  default:
		     break;
	     }
	 }	
        usleep(800);
     }
     
    return 0;
}

#endif    /* FRAME_SUPPORT_MOUSE */

/* main */
int main(int argc, char *argv[]) 
{
    fb_info fb_inf;
    
    if (init_fb(&fb_inf) < 0)
    {
    	  fprintf(stderr, "Error initial framebuffer\b")	;
    	  return -1;
    }
    
  #ifdef FRAME_SUPPORT_JPEG
    display_jpeg("test0.jpg", fb_inf);
    sleep(1);
    display_jpeg("test1.jpg", fb_inf);
    sleep(1);
  #endif

  #ifdef FRAME_SUPPORT_BMP
    display_bmp(fb_inf, "test.bmp");
    sleep(1);
  #endif
     
    /* draw a squarearea */
    fb_draw_squarearea(fb_inf, 0, 0, fb_inf.w, fb_inf.h, 0xFF0000);
    
    /* draw five triangle */    
    fb_draw_star(fb_inf, 200, 220, 150, 0x00FFFF00);
    
    fb_draw_star(fb_inf, 380, 70, 40, 0x00FFFF00);	
    fb_draw_star(fb_inf, 440, 170, 40, 0x00FFFF00);
    fb_draw_star(fb_inf, 430, 270, 40, 0x00FFFF00);
    fb_draw_star(fb_inf, 380, 370, 40, 0x00FFFF00);
    
  #ifdef FRAME_SUPPORT_FONT
    if (init_ft("mao.ttf", 64) < 0)
    {
    	  fprintf(stderr, "Error initial font\b")	;
    	  return -1;
    }
    
    display_string ("北京 中关村", 10, fb_inf.h - 100, fb_inf,0x00FFFF00);
  #endif
    
  #ifdef FRAME_SUPPORT_MOUSE
    test_mouse(fb_inf);
  #endif

    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
    
    return 0;
}
