/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:17:26 by mlektaib          #+#    #+#             */
/*   Updated: 2023/01/18 14:02:32 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	resetall(int *client, int pid, unsigned char *c, int *b)
{
	if (*client != pid)
	{
		write(1, "\n", 1);
	}
	*client = pid;
	*c = 0;
	*b = 128;
}

void	ft_begofuni(unsigned char *tab, int *start, unsigned char c)
{
	int	i;

	i = 0;
	tab[0] = c;
	while (i < 4)
	{
		if (c & 128)
			*start += 1;
		i++;
		c <<= 1;
	}
}

void	ft_handleunicode(unsigned char c, int pid)
{
	static int				start;
	static unsigned char	tab[4];
	static int				bytes;
	static int				oldpid;

	if (pid != oldpid)
	{
		oldpid = pid;
		start = 0;
	}
	if (start == 0 || pid != oldpid)
	{
		bytes = 0;
		ft_begofuni(tab, &start, c);
	}
	else if (start > 1)
		tab[bytes] = c;
	else if (start == 1)
	{
		tab[bytes] = c;
		write(1, tab, bytes + 1);
	}
	bytes++;
	start--;
}

void	handler(int sig, siginfo_t *si)
{
	static unsigned char	c;
	static int				b;
	static int				client;

	if (client != si->si_pid || b == 0)
		resetall(&client, si->si_pid, &c, &b);
	c += (sig - 30) * b;
	b = b / 2;
	if (b == 0)
	{
		if (c >= 128)
			ft_handleunicode(c, si->si_pid);
		if (c < 128)
			write(1, &c, 1);
		if (c == '\0')
		{
			usleep(300);
			kill(client, SIGUSR2);
		}
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_handler = (void *)handler;
	pid = getpid();
	write(1, "server pid :", 13);
	ft_putnbr(pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause ();
	}
	return (0);
}
