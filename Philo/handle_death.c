/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:21:54 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/20 20:06:17 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death_of_a_philo(t_philo *philo)
{
	long	last_meal;
	long	time_to_die;

	pthread_mutex_lock(&(philo->rules->lock_death));
	time_to_die = philo->rules->time_die;
	pthread_mutex_unlock(&(philo->rules->lock_death));
	pthread_mutex_lock(&(philo->rules->lock_access_rules));
	last_meal = ft_get_timestamp(philo->rules->start_time) - philo->last_meal;
	pthread_mutex_unlock(&(philo->rules->lock_access_rules));
	if (last_meal >= time_to_die)
	{
		philo->is_dead = 1;
		return (1);
	}
	return (0);
}

int	ft_check_all_philos_are_done(t_philo **philo)
{
	int				id;
	int				number;

	id = 0;
	pthread_mutex_lock(&((*philo)->rules->lock_access_rules));
	number = (*philo)->rules->philo_nb;
	pthread_mutex_unlock(&((*philo)->rules->lock_access_rules));
	while (id < number)
	{
		if (ft_check_done_philo(&((*philo)[id])))
			id++;
		else
			return (0);
	}
	return (1);
}

static void	ft_behaviour_after_death(t_rules_philo *rules, t_philo *philo)
{
	pthread_mutex_lock(&(rules->lock_death));
	rules->is_a_dead = 1;
	ft_state_msg_death(DEATH, philo);
	pthread_mutex_unlock(&(rules->lock_death));
	pthread_mutex_unlock(&(philo->right_fork->lock_fork));
	pthread_mutex_unlock(&(philo->left_fork->lock_fork));
}

void	*ft_check_death_of_all_philos(void *data)
{
	t_philo			**philosophes;
	t_rules_philo	*rules;
	int				id;

	id = 0;
	philosophes = (t_philo **)(data);
	rules = (*philosophes)->rules;
	while (1)
	{
		id = 0;
		if (ft_check_all_philos_are_done(philosophes))
			return (NULL);
		while (id < rules->philo_nb)
		{
			if (ft_check_death_of_a_philo(&((*philosophes)[id])))
			{	
				ft_behaviour_after_death(rules, &(*philosophes)[id]);
				return (NULL);
			}
			id++;
		}
		ft_usleep(1);
	}
}
