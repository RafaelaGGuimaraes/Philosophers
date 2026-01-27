/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:31:24 by rgomes-g          #+#    #+#             */
/*   Updated: 2026/01/27 15:06:48 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_data *data, t_philo *philos)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &philo_routine,
				&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	aux_dead(t_data *data, t_philo *philos, int i)
{
	long long	time;

	if (get_time() - philos[i].last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->monitor_lock);
		if (data->stop_simulation == 1)
		{
			pthread_mutex_unlock(&data->monitor_lock);
			pthread_mutex_unlock(&philos[i].philo_lock);
			return (1);
		}
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->monitor_lock);
		time = get_time() - data->start_time;
		pthread_mutex_lock(&data->print_lock);
		printf("%lld %d %s\n", time, philos[i].id, "died 💀");
		pthread_mutex_unlock(&data->print_lock);
		pthread_mutex_unlock(&philos[i].philo_lock);
		return (1);
	}
	return (0);
}

static int	philo_has_died(t_data *data, t_philo *philos)
{
	int			i;

	i = 0; 
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&philos[i].philo_lock);
		if (get_time() - philos[i].last_meal_time > data->time_to_die)
		{
			aux_dead(data, philos, i);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].philo_lock);
		i++;
	}
	return (0);
}

static int	all_philos_eaten(t_data *data, t_philo *philos)
{
	int	i;
	int	finished_philos;

	if (data->eat_count_max <= 0)
		return (0);
	i = 0;
	finished_philos = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&philos[i].philo_lock);
		if (philos[i].meals_eaten >= data->eat_count_max)
			finished_philos++;
		pthread_mutex_unlock(&philos[i].philo_lock);
		i++;
	}
	if (finished_philos == data->num_philos)
		return (1);
	return (0);
}

void	monitor(t_data *data, t_philo *philos)
{
	while (1)
	{
		if (philo_has_died(data, philos)
			|| all_philos_eaten(data, philos))
		{
			pthread_mutex_lock(&data->monitor_lock);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->monitor_lock);
			return ;
		}
		usleep(900);
	}
}
