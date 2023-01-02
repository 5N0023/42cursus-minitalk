#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void makezeros(char *unicode,int **uni,int *unibytes,int *count)
{
	int i;

	i = 0;
	while (i < 4)
	{
		unicode[i] = 0;
		i++;
	}
	**uni = 0;
	*unibytes = 0;
	*count = 0;
}

void unicodehandler(int *uni,int *b,siginfo_t *si)
{
	static int unibytes;
	static char unicode[4];
	static int client;
	static int count;
	
	if(client != si->si_pid || b == 0)
	{
		client = si->si_pid;
		makezeros(unicode,&uni,&unibytes,&count);
	}
	if (*b > 16 && *uni != 2)
	{
		unibytes++;
		*uni = 1;
		printf("here\n");
	}
	else if (*b < 16 && *uni == 1)
		*uni = 2;
	unicode[count] += *b;
	if (b == 0)
	{
		count++;
		*b = 128;
	}
	if (count == unibytes)
		write(1,&unicode,unibytes);
}
void handler(int sig, siginfo_t *si) 
{
	static char c;
	static int b;
	static int client;
	static int unicode;

	if(client != si->si_pid || b == 0)
	{
		client = si->si_pid;
		c = 0;
		b = 128;
	}
	if(sig == SIGUSR2 || unicode > 0)
		unicodehandler(&unicode,&b,si);
	else if (sig == SIGUSR2 && unicode == 0)
		c += b;
	b  = b / 2;
	if (b == 0 && unicode == 0)
	{
		write(1,&c,1);
		if(c == 0)
		{
			write(1,"\n",1);
			kill(si->si_pid,SIGUSR2);
		}
	}
}
int main(void)
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