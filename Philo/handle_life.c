/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:55:51 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/16 16:47:40 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_life_philo(void *data)
{
	t_philo	*philo;
	long	start_time;

	philo = (t_philo *)data;
	if (philo->philo_id % 2)
	{
		pthread_mutex_lock(&(philo->rules->lock_writing));
		printf("Le philosophe %d est en train de dormir\n", philo->philo_id);
		pthread_mutex_unlock(&(philo->rules->lock_writing));
		usleep(philo->rules->time_eat);
	}
	while (!philo->is_done && !philo->is_dead)
	{
		ft_get_right_fork(philo);
		ft_get_left_fork(philo);
		ft_lets_eat(philo);
		ft_lets_sleep_and_think(philo);
	}
	return (NULL);	
}
