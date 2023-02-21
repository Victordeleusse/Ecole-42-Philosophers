/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:55:51 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/21 14:32:28 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_odd_life(t_philo *philo)
{
	if (!(philo->philo_id % 2))
	{
		ft_state_msg(SLEEP, philo);
		ft_usleep(philo->rules->time_eat);
	}
}

void	*ft_life_philo(void *data)
{
	t_philo	*philo;
	int		number;
	long	time_to_die;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->rules->lock_access_rules);
	number = philo->rules->philo_nb;
	time_to_die = philo->rules->time_die;
	pthread_mutex_unlock(&philo->rules->lock_access_rules);
	if (number == 1)
		ft_usleep(time_to_die + 200);
	ft_odd_life(philo);
	while (!ft_check_done_philo(philo) && !ft_check_death_of_a_philo(philo))
	{
		if ((philo->philo_id % 2))
		{
			if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
				|| philo->rules->is_a_dead)
				break ;
			ft_get_right_fork(philo);
			if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
				|| philo->rules->is_a_dead)
			{
				pthread_mutex_unlock(&(philo->right_fork->lock_fork));
				break ;
			}	
			ft_get_left_fork(philo);
		}
		else
		{
			if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
				|| philo->rules->is_a_dead)
				break ;
			ft_get_left_fork(philo);
			if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
				|| philo->rules->is_a_dead)
			{	
				pthread_mutex_unlock(&(philo->left_fork->lock_fork));
				break ;
			}
			ft_get_right_fork(philo);
		}
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
			|| philo->rules->is_a_dead)
		{	
			pthread_mutex_unlock(&(philo->right_fork->lock_fork));
			pthread_mutex_unlock(&(philo->left_fork->lock_fork));
			break ;
		}
		ft_lets_eat(philo);
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
			|| philo->rules->is_a_dead)
			break ;
		ft_lets_sleep_and_think(philo);
	}
	return (NULL);
}
