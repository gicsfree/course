/* time/date */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define SECOND_PER_YEAR 365*24*60*60UL

int main (int argc, char** argv)
{
    struct timeval tm_get;
    struct tm *ltm;
    char tm_buf[sizeof(struct tm)] = {0};
    
    gettimeofday(&tm_get, NULL);
    
    printf(" Get linux system time is : %lld s\n", (long long)tm_get.tv_sec);
    
    ltm = localtime(&tm_get.tv_sec);
    
    printf(" Get linux system time(year) is : %d\n", ltm->tm_year + 1900);
    printf(" Get linux system time(month) is : %d\n", ltm->tm_mon + 1);
    printf(" Get linux system time(day) is : %d\n", ltm->tm_mday);
    printf(" Get linux system time(week) is : %d\n", ltm->tm_wday);
    printf(" Get linux system time(hour) is : %d\n", ltm->tm_hour);
    printf(" Get linux system time(minute) is : %d\n", ltm->tm_min);
    printf(" Get linux system time(second) is : %d\n", ltm->tm_sec);         
    
    strcpy((char*)tm_buf, (char*)asctime(ltm));

    printf(" Get linux system is : %s ", tm_buf);
    
    return 0;
}
