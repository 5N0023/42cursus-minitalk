#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig,siginfo_t *si) 
{
    
	static char c;
	static int b = 128;
	if (sig == SIGUSR2)
	{
		c += b;
	}
	else if(sig == SIGUSR1){}
	b  = b / 2;
	if (b == 0)
	{
		write(1,&c,1);
		if(c == 0)
		{
			write(1,"\n",1);
			kill(si->si_pid,SIGUSR2);
		}
		b = 128;
		c = 0;
	}
}
int main()
{
	pid_t pid = getpid();
	printf("server pid is %d \n",pid);
	struct sigaction sa;
	sa.sa_handler = (void*)handler;
	while(1)
	{
		sigaction(SIGUSR1,&sa,NULL);
		sigaction(SIGUSR2,&sa,NULL);
		pause();
	}
}