/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:16:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/01/17 16:51:37 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig)
{
	if (sig == SIGUSR2)
		write(1, "message sent successfully", 26);
}

void	client(char c, int pid)
{
	int				i;

	i = 0;
	while (i < 8)
	{
		if (c & 128)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		c <<= 1;
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	signal(SIGUSR2, handler);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			client(argv[2][i], pid);
			i++;
		}
		client('\0', pid);
		pause();
	}
	else
	{
		write(2, "Error: wrong format.\n", 22);
		return (1);
	}
	return (0);
}
