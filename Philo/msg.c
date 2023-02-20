/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:23:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/20 20:09:28 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

void	ft_state_msg(char *str, t_philo *philo)
{
	long	curr_time;
	long	start_time;

	pthread_mutex_lock(&(philo->rules->lock_writing));
	start_time = philo->rules->start_time;
	curr_time = ft_get_timestamp(start_time);
	if (!philo->rules->is_a_dead)
		printf("%ld %d %s\n", curr_time, philo->philo_id, str);
	pthread_mutex_unlock(&(philo->rules->lock_writing));
}

void	ft_state_msg_death(char *str, t_philo *philo)
{
	long	curr_time;
	long	start_time;

	pthread_mutex_lock(&(philo->rules->lock_writing));
	start_time = philo->rules->start_time;
	curr_time = ft_get_timestamp(start_time);
	printf("%ld %d %s\n", curr_time, philo->philo_id, str);
	pthread_mutex_unlock(&(philo->rules->lock_writing));
}

void	ft_free_philos_forks(t_philo **philosophes, t_fork **forks)
{
	pthread_mutex_destroy(&(*philosophes)->lock_nb_of_meal);
	pthread_mutex_destroy(&(*philosophes)->lock_done);
	pthread_mutex_destroy(&(*philosophes)->rules->lock_access_rules);
	pthread_mutex_destroy(&(*philosophes)->rules->lock_death);
	pthread_mutex_destroy(&(*philosophes)->rules->lock_writing);
	pthread_mutex_destroy(&(*forks)->lock_fork);
	free(*philosophes);
	free(*forks);
}
