#include "minitalk.h"


void client(char c,int pid)
{
	int				i;

	i = 0;
	while(i < 8)
	{
		if (c & 128)
			kill(pid,SIGUSR2);
		else 
			kill(pid,SIGUSR1);
		i++;
		c <<= 1;
		usleep(300);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			client(argv[2][i], pid);
			i++;
		}
		client(pid,0);
	}
	else
	{
		write(2,"Error: wrong format.\n",22);
		return (1);
	}
	return (0);
}