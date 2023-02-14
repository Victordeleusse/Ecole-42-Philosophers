/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:21:54 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/14 20:19:49 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death_of_a_philo(t_philo *philo)
{
	long	last_meal;
	
	pthread_mutex_lock(&(philo->lock_last_meal));
	last_meal = ft_get_timestamp(philo->rules->start_time) - philo->last_meal; 
	pthread_mutex_unlock(&(philo->lock_last_meal));
	if (last_meal >= philo->rules->time_die)
	{
		pthread_mutex_lock(&(philo->lock_is_dead));
		philo->is_dead = 1;
		printf("Le philosophe %d est mort\n", philo->philo_id);
		pthread_mutex_unlock(&(philo->lock_is_dead));
		return (1);
	}
	return (0);
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
		while (id < rules->philo_nb)
		{
			if (ft_check_death_of_a_philo(&((*philosophes)[id])))
			{
				pthread_mutex_lock(&(rules->lock_death));
				rules->one_dead = 1;
				pthread_mutex_unlock(&(rules->lock_death));
				return (NULL);
			}
			id++;
		}
		usleep(100);
	}
}