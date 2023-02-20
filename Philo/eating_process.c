/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:17:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/20 20:16:57 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_done_philo(t_philo *philo)
{
	int		nb_mandatory_meal;

	pthread_mutex_lock(&(philo->lock_nb_of_meal));
	nb_mandatory_meal = philo->rules->nb_must_eat;
	pthread_mutex_unlock(&(philo->lock_nb_of_meal));
	if (philo->nb_of_meal >= nb_mandatory_meal)
	{	
		pthread_mutex_lock(&(philo->lock_done));
		philo->is_done = 1;
		pthread_mutex_unlock(&(philo->lock_done));
		return (1);
	}
	return (0);
}

void	ft_lets_sleep_and_think(t_philo *philo)
{	
	ft_check_done_philo(philo);
	if (philo->is_done)
		return ;
	ft_state_msg(SLEEP, philo);
	ft_usleep(philo->rules->time_slp);
	ft_state_msg(THINK, philo);
	ft_usleep(philo->rules->time_thk);
}

void	ft_get_right_fork(t_philo *philo)
{
	if (!philo->is_done && !ft_check_death_of_a_philo(philo))
	{
		pthread_mutex_lock(&(philo->right_fork->lock_fork));
		ft_state_msg(FORK, philo);
	}
}

void	ft_get_left_fork(t_philo *philo)
{	
	if (!philo->is_done && !ft_check_death_of_a_philo(philo))
	{
		pthread_mutex_lock(&(philo->left_fork->lock_fork));
		ft_state_msg(FORK, philo);
	}
}

void	ft_lets_eat(t_philo *philo)
{
	ft_state_msg(EAT, philo);
	pthread_mutex_lock(&(philo->rules->lock_access_rules));
	philo->nb_of_meal++;
	philo->last_meal = ft_get_timestamp(philo->rules->start_time);
	pthread_mutex_unlock(&(philo->rules->lock_access_rules));
	ft_usleep(philo->rules->time_eat);
	pthread_mutex_unlock(&(philo->left_fork->lock_fork));
	pthread_mutex_unlock(&(philo->right_fork->lock_fork));
}
