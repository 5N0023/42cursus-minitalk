/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:16:29 by mlektaib          #+#    #+#             */
/*   Updated: 2023/01/17 16:49:52 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *si)
{
	static char	c;
	static int	b;
	static int	client;

	if (client != si->si_pid || b == 0)
	{
		if (client != si->si_pid)
			write(1, "\n", 1);
		client = si->si_pid;
		c = 0;
		b = 128;
	}
	else if (sig == SIGUSR2)
		c += b;
	b = b / 2;
	if (b == 0)
		write(1, &c, 1);
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
