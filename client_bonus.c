#include <signal.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>


void handler(int sig)
{
	if(sig == SIGUSR2)
		write(1,"message sent successfully",26);
}

void client(char *msg,int pid)
{
	unsigned char	c;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while(msg[i])
		{
			c = msg[i];
			while(j < 8)
			{
				if (c & 128)
					kill(pid,SIGUSR2);
				else 
					kill(pid,SIGUSR1);
				j++;
				c <<= 1;
				usleep(200);
			}
			j=0;
			i++;
		}
}

int main(int ac,char **arg)
{
	int pid;
	int i;

	if (ac != 3)
		exit(1);
	pid = atoi(arg[1]);
	signal(SIGUSR2,handler);
	client(arg[2],pid);
	i = 0;
	while(i < 8)
		{
			kill(pid,SIGUSR1);
			usleep(200);
			i++;
		}
	return (0);
}