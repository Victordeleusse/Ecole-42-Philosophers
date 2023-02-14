/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:16:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/14 20:04:29 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_create(&((*rules).death_check), NULL, &ft_check_death_of_all_philos, philosophes) == 0)
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
