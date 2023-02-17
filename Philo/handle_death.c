/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:21:54 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/17 13:41:57 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death_of_a_philo(t_philo *philo)
{
	long	last_meal;
	long	time_limit;
	
	pthread_mutex_lock(&(philo->lock_last_meal));
	last_meal = ft_get_timestamp(philo->rules->start_time) - philo->last_meal; 
	time_limit = philo->rules->time_die;
	pthread_mutex_unlock(&(philo->lock_last_meal));
	if (last_meal >= time_limit)
	{
		philo->is_dead = 1;
		ft_state_msg(DEATH, philo);
		return (1);
	}
	return (0);
}

int	ft_check_all_philos_are_done(t_philo **philo)
{
	int				id;
	t_rules_philo	*rules;
	
	id = 0;
	rules = (*philo)->rules;
	while (id < rules->philo_nb)
	{
		if ((*philo)[id].is_done == 1)
			id++;
		else
			return (0);
	}
	return (1);
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
			exit(EXIT_SUCCESS);
		while (id < rules->philo_nb)
		{
			if (ft_check_death_of_a_philo(&((*philosophes)[id])))
			{
				pthread_mutex_lock(&(rules->lock_death));
				rules->one_dead = 1;
				exit(EXIT_FAILURE);
				pthread_mutex_unlock(&(rules->lock_death));
				return (NULL);
			}
			id++;
		}
		ft_usleep(10);
	}
}
