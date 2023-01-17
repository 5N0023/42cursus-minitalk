/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:16:54 by mlektaib          #+#    #+#             */
/*   Updated: 2023/01/17 16:51:01 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	size_t	res;
	int		sign;
	size_t	prev;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		prev = res;
		res = (*str - 48) + (res * 10);
		if (res / 10 != prev && sign == 1)
			return (-1);
		if (res / 10 != prev && sign == -1)
			return (0);
			str++;
	}
	return ((int)res * sign);
}

void	ft_putnbr(int n)
{
	long	ln;
	char	nm;

	ln = n;
	if (ln < 0)
	{
		write(1, "-", 1);
		ln *= -1;
	}
	if (ln <= 9)
	{
		nm = ln + '0';
		write(1, &nm, 1);
	}
	else
	{
		ft_putnbr(ln / 10);
		ft_putnbr(ln % 10);
	}
}
