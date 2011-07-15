/* dir_dir.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

static int get_info(const char * filename)
{
    struct stat statbuf;
    
    if(stat(filename, &statbuf) == -1)
    {
        printf("@@: %s\n",filename);
        return(0);
    }
    
    if(S_ISDIR(statbuf.st_mode))
    {
        printf("%s\t(dir)\tmodified at %s", filename, ctime(&statbuf.st_mtime));
    }
    
    if(S_ISREG(statbuf.st_mode))
    {
         printf("%s\tsize:%ld bytes\n", filename, statbuf.st_size);
         return(0);
    }
    
    return (1);
}

/* main.c */
int main(int argc,char **argv)
{
    DIR * dirp = NULL;
    struct dirent * direntp = NULL;
    
    if(argc < 2)
    {
        printf("Enter Params Must >= 2\n");
        return (-1);	
    }
     
    if((dirp = opendir(argv[1])))
    {  	
        while((direntp = readdir(dirp)) != NULL)
        {
            get_info(direntp->d_name);           
        }
        closedir(dirp);
    }
    return (0);
}
