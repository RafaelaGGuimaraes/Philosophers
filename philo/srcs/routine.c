/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:28:24 by rgomes-g          #+#    #+#             */
/*   Updated: 2026/02/05 09:29:36 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	which_philo(t_philo *p,
	pthread_mutex_t **first, pthread_mutex_t **second)
{
	if (p->id % 2 == 0)
	{
		*first = p->left_fork;
		*second = p->right_fork;
	}
	else
	{
		*first = p->right_fork;
		*second = p->left_fork;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	which_philo(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork 🍴");
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_action(philo, "has taken a fork 🍴");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal_time = get_curent_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_lock);
	print_action(philo, "is eating 🍝");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 || (philo->data->num_philos % 2 != 0
			&& philo->id == philo->data->num_philos))
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->monitor_lock);
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&philo->data->monitor_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->monitor_lock);
		philo_eat(philo);
		print_action(philo, "is sleeping 💤");
		ft_usleep(philo->data->time_to_sleep);
		print_action(philo, "is thinking 💭");
		if (philo->data->num_philos % 2 != 0)
			usleep(1000);
	}
	return (NULL);
}
