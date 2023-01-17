/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:16:50 by mlektaib          #+#    #+#             */
/*   Updated: 2023/01/17 16:51:22 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	client(char c, int pid)
{
	int				i;

	i = 0;
	while (i < 8)
	{
		usleep(200);
		if (c & 128)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		c <<= 1;
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
	}
	else
	{
		write(2, "Error: wrong format.\n", 22);
		return (1);
	}
	return (0);
}
