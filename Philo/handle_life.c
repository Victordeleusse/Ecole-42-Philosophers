/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:55:51 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/16 18:46:13 by vde-leus         ###   ########.fr       */
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
		ft_state_msg(SLEEP, philo);
		usleep(philo->rules->time_eat);
	}
	while (!philo->is_dead)
	{
		ft_get_right_fork(philo);
		ft_get_left_fork(philo);
		ft_lets_eat(philo);
		if (philo->is_done)
			break;
		ft_lets_sleep_and_think(philo);
	}
	return (NULL);	
}
