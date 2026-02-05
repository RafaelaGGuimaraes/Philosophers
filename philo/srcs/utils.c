/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:30:44 by rgomes-g          #+#    #+#             */
/*   Updated: 2026/02/05 09:01:36 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < mls)
		usleep(500);
}

void	print_action(t_philo *philo, char *str)
{
	long long	time;
	int			stop;

	pthread_mutex_lock(&philo->data->monitor_lock);
	stop = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->monitor_lock);
	if (!stop)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
}

void	destroy_all(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->monitor_lock);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&philo[i].philo_lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(philo);
}
