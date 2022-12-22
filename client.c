#include <signal.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>


void handler(int sig)
{
	if(sig == SIGUSR2)
		{
			write(1,"message sent successfully",26);
		}
}


int main(int ac,char **arg)
{
	int j = 0;
	pid_t pid = atoi(arg[1]);
	unsigned char c;
	int i = 0;
	if (ac != 3)
		exit(1);
	while(arg[2][i])
	{
		c = arg[2][i];
		while(j < 8)
		{
			if (c & 128)
				kill(pid,SIGUSR2);
			else 
				kill(pid,SIGUSR1);
			j++;
			c <<= 1;
			usleep(300);
		}
		j=0;
		i++;
	}
	j = 0;
	while(j < 8)
		{
			kill(pid,SIGUSR1);
			usleep(300);
			j++;
		}
	j = 0;
	pause();
	signal(SIGUSR2,handler);
}