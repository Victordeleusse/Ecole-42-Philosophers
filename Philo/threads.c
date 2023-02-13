/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:16:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/13 20:36:09 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_life_philo(void *data)
{
	t_philo	*philo;
	long	start_time;

	philo = (t_philo *)data;
	if (philo->philo_id % 2)
		usleep(philo->rules->time_eat);
	while (!philo->is_done && !philo->is_dead && !philo->rules->one_dead)
	{
		ft_get_right_fork
		ft_get_left_fork
		eat;
		ft_release_right_fork
		ft_release_left_fork
		sleep;
		think;
	}
		
}

void	*ft_death_sentence(void *data)
{
	
}

int	ft_generate_threads(t_philo **philosophes, t_rules_philo *rules)
{
	int	id;

	id = 0;
	rules->start_time = ft_get_timestamp(0);
	while (id < rules->philo_nb)
	{
		if (pthread_create(&((*philosophes)[id].thread_id), NULL, &ft_life_philo, &((*philosophes)[id])) == 0)
			return (1);
		id++;
	}
	if (pthread_create(&((*rules).death_check), NULL, &ft_death_sentence, rules) == 0)
			return (1);
	return (0);
}

void	ft_join_threads(t_philo **philosophes, t_rules_philo *rules)
{
	int	id;

	id = 0;
	while (id < rules->philo_nb)
	{	
		if	(pthread_join(&((*philosophes)[id].thread_id), NULL))
			return (2);
		id++;
	}
	if (pthread_join(&((*rules).death_check), NULL))
		return (2);
	return (0);
}
