#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void unicodehandler(int *unicode,int b)
{
	printf("here\n");
}
void handler(int sig, siginfo_t *si) 
{
	static char c;
	static int b;
	static int client;

	if(client != si->si_pid || b == 0)
	{
		client = si->si_pid;
		c = 0;
		b = 128;
	}
	else if (sig == SIGUSR2)
		c += b;
	b  = b / 2;
	if (b == 0)
	{
		write(1,&c,1);
		if(c == 0)
			write(1,"\n",1);
	}
}
int main(void)
{
	pid_t pid ;
	struct sigaction sa;

	pid = getpid();
	printf("server pid is %d \n",pid);
	sa.sa_handler = (void*)handler;
	while(1)
	{
		sigaction(SIGUSR1,&sa,NULL);
		sigaction(SIGUSR2,&sa,NULL);
		pause();
	}
}