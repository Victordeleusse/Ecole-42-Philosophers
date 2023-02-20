/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:21:54 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/20 15:30:47 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death_of_a_philo(t_philo *philo)
{
	long	last_meal;
	
	last_meal = ft_get_timestamp(philo->rules->start_time) - philo->last_meal; 
	if (last_meal >= philo->rules->time_die)
	{
		philo->is_dead = 1;
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
	int				stop;

	id = 0;
	stop = 0;
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
				pthread_mutex_lock(&(rules->lock_death));
				rules->is_a_dead = 1;
				pthread_mutex_unlock(&(rules->lock_death));
				ft_state_msg_death(DEATH, &(*philosophes)[id]);
				return (NULL) ;
			}
			id++;
		}
		ft_usleep(1);
	}
}
