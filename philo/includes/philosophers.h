/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:31:55 by rgomes-g          #+#    #+#             */
/*   Updated: 2026/02/10 15:16:00 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	int				eat_count_max;
	int				num_philos;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	*forks;
	int				stop_simulation;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	philo_lock;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

int			check_args(int argc, char **argv, t_data *data);
int			main(int argc, char **argv);
int			init_global_data(t_data *data);
int			init_philos(t_philo **philo, t_data *data);
int			start_simulation(t_data *data, t_philo *philo);
int			ft_atou(const char *str);
int			is_valid(int argc, char **argv);
int			check_error(int argc, char **argv);
long long	get_curent_time(void);
void		ft_usleep(size_t mls);
void		print_action(t_philo *philo, char *str);
void		philo_eat(t_philo *philo);
void		*philo_routine(void *arg);
void		destroy_all(t_data *data, t_philo *philo);
void		monitor(t_data *data, t_philo *philo);

#endif