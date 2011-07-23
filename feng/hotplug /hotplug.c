/* hotplug.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <unistd.h>

#define UEVENT_BUFFER_SIZE 2048

static int init_hotplug_sock()
{
    const int buffersize = 1024;
    int ret;

    struct sockaddr_nl snl;
    bzero(&snl, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
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
int hot_plug(void)
{
    int hotplug_sock = init_hotplug_sock();
    
    while(1)
    {
        /* Netlink Message Buffer */
        char buf[UEVENT_BUFFER_SIZE * 2] = {0};
        
        recv(hotplug_sock, &buf, sizeof(buf), 0);
        
        printf("%s\n", (char*)buf);   
    }
    return 0;
}

/**************************************************************************
* main
**************************************************************************/
int main(int argc, char* argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("child process id is %d\n", getpid());    	
        hot_plug();
    }
    else
    {
        printf("parent process id is %d\n", getpid());
    }

    return 0;
}
