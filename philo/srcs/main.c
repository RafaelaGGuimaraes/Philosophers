/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:24:01 by rgomes-g          #+#    #+#             */
/*   Updated: 2026/01/27 14:54:07 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv, t_data *data)
{
	if (error_arg(argc, argv))
		return (1);
	data->num_philos = ft_atou(argv[1]);
	data->time_to_die = ft_atou(argv[2]);
	data->time_to_eat = ft_atou(argv[3]);
	data->time_to_sleep = ft_atou(argv[4]);
	data->stop_simulation = 0;
	if (argc == 6)
		data->eat_count_max = ft_atou(argv[5]);
	else
		data->eat_count_max = 0;
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
	{
		printf("Error: All parameters must be greater than one.");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	int			i;

	if (check_args(argc, argv, &data))
		return (1);
	if (init_global_data(&data))
		return (1);
	if (init_philos(&philos, &data))
	{
		printf("Error: Falied to initialize philosophers.\n");
		free(data.forks);
		return (1);
	}
	if (start_simulation(&data, philos))
		return (1);
	monitor(&data, philos);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	cleanup(&data, philos);
	return (0);
}
