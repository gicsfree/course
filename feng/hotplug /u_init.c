//测试优盘挂载思路   仅供参考

/* hotplug.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>

#define UEVENT_BUFFER_SIZE 2048

int sdd_flag = 0;

int is_dir(char *dirname);

static int double_lock = 0;

static int init_hotplug_sock()
{
    const int buffersize = 1024;
    int ret;

    struct sockaddr_nl snl;
    bzero(&snl, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = pthread_self();   //huo qu zi shen xian cheng ID
    snl.nl_groups = 1;

    int s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (s == -1) 
    {
        perror("socket");
        return -1;
    }
    setsockopt(s, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));

    ret = bind(s, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
    if (ret < 0) 
    {
        perror("bind faliuer !!!\n");
        close(s);
        return -1;
    }

    return s;
}

/**************************************************************************
* main
**************************************************************************/
void * u_init()
{
    int count = 0;
    char name[6];
    char command[2][35];
    char * dev_name = NULL;

    int hotplug_sock = init_hotplug_sock();
    
    while(1)
    {
        /* Netlink Message Buffer */
        char buf[UEVENT_BUFFER_SIZE * 2] = {0};
        
        recv(hotplug_sock, &buf, sizeof(buf), 0); 
	
	   if (strncmp((char*)buf, "add", 3) == 0)
	   {
		count++;
		if (13 == count)
		{
		    if ((dev_name = strrchr((char *)buf, '/')) != NULL)
		    {
			strncpy(name, dev_name, 5);
			dev_name = NULL;
		    	sprintf(command[0],"sudo umount /dev%s", name);          //找到设备“/sdb1"  字符模式下 需先卸载后挂载
		    	sprintf(command[1],"sudo mount /dev%s /mnt/sdd", name);   

     		       printf("load...\n");
    		       sleep(4);
			if (is_dir("/mnt/sdd") == 0)
			{
    		           system("sudo mkdir /mnt/sdd");
			}
    		       system(command[0]);
    		       usleep(800);
    		       system(command[1]);
		       printf("U is ok!\n");
		       sdd_flag = 1;
		       count = 0;
		       memset(name, 0, 5);
		       memset(command[0], 0, 35);
	 	       memset(command[1], 0, 35);
		    }
		    else
		    	printf("cann't find the map!\n");
		}	 
	   }
	   if (strncmp((char*)buf, "rem", 3) == 0)
	   {
		sdd_flag = 0;
	   }
	//   printf("%d\n",flag);
    }

    pthread_exit(NULL);
}

/*************************************************************************
*is dir?
*************************************************************************/
int is_dir(char *dirname)
{
    if(opendir(dirname) == NULL)
	return 0;
    else
	return 1;    
}




#if 1
/**************************************************************************
* main
**************************************************************************/
int main(int argc, char* argv[])
{
    pthread_t thread[1];
    pthread_mutex_t mut;
    int temp;

    pthread_mutex_init(&mut, NULL);

    memset(&thread, 0, sizeof(thread));

    if ((temp = pthread_create(&thread[0], NULL, u_init, NULL)) != 0)  
    {
       printf("U盘更新线程创建失败!\n");
    }

    if (thread[0] != 0)
     {
       pthread_join(thread[0], NULL);
       printf("U盘更新线程已经结束\n");
     }

    return 0;
}
#endif
