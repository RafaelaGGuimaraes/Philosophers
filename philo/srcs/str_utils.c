/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:23:57 by rgomes-g          #+#    #+#             */
/*   Updated: 2026/01/28 09:48:22 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atou(const char *str)
{
	long	n;

	n = 0;
	if (!*str)
		return (0);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (n > INT_MAX / 10 || (n == INT_MAX
				/ 10 && (*str - '0') > INT_MAX % 10))
			return (0);
		n = (n * 10) + (*str - '0');
		str++;
	}
	return (n);
}

int	is_valid(int argc, char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		while (argv[j][i] == ' ' || argv[j][i] == '+'
				|| (argv[j][i] >= 9 && argv[j][i] <= 13))
			i++;
		if (argv[j][i] < '0' || argv[j][i] > '9')
			return (1);
		while (argv[j][i] >= '0' && argv[j][i] <= '9')
			i++;
		if (argv[j][i])
			return (1);
		j++;
	}
	return (0);
}

int	error_arg(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	if (is_valid(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	return (0);
}
