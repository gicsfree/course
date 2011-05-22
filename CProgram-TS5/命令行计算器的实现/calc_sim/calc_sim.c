/* calc_a_s.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* add */
long long calc_add( int a1, int a2)
{
    long long result = 0;
    
    result = (long long)a1 + (long long)a2;
    
    return result;
}

/* sub */
long long calc_sub(int s1, int s2)
{
    long long result = 0;
    
    result = (long long)s1 - (long long)s2;
    
    return (result);
}

/* main */
int main (int argc, char** argv)    // Have Problems! Do you know why?
{
	  unsigned int calc_mod = 0;
	  int idata  = 0;
    int kdata  = 0;
    long long result = 0;
    
    if(argc < 2)
    {
    	 printf("enter cmd numbers must > 2!!!\n");
    	 return -1;
    }
    argv ++;
    calc_mod = atoi(*argv);
    argv ++;    
    idata = atoi(*argv);
    argv ++;    
    kdata = atoi(*argv);    
    
    printf("Enter is mod<%d> data_f<%d> data_b<%d> \n", calc_mod, idata, kdata);
    
    switch(calc_mod)
    {
    	    case 1:
    	    	    result = calc_add(idata, kdata);   
                printf("Calc add (%d + %d) result is %d\n", idata, kdata, (int)result);  	    	
    	    	break;
    	    	
    	    case 2:
    	    	    result = calc_sub(idata, kdata);
                printf("Calc sub (%d - %d) result is %d\n", idata, kdata, (int)result);     	    	    
    	    	break;
    	    	
    	    default:
    	    	    printf("Enter calc mod error!!!\n");
    	    	break;
    }
    
    return 0;
}
