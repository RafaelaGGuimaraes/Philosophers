/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:26:03 by rgomes-g          #+#    #+#             */
/*   Updated: 2026/02/04 14:21:02 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_global_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL)
		|| pthread_mutex_init(&data->monitor_lock, NULL))
	{
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philos(t_philo **philo, t_data *data)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philo)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].meals_eaten = 0;
		if (pthread_mutex_init(&(*philo)[i].philo_lock, NULL))
			return (1);
		(*philo)[i].left_fork = &data->forks[i];
		(*philo)[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}
