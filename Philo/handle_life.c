/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:55:51 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/20 13:40:47 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_life_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2)
	{
		ft_state_msg(SLEEP, philo);
		ft_usleep(philo->rules->time_eat);
	}
	while (!philo->is_dead && !philo->is_done)
	{
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo))
			break;
		ft_get_right_fork(philo);
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo))
			break;
		ft_get_left_fork(philo);
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo))
			break;
		ft_lets_eat(philo);
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo))
			break;
		ft_lets_sleep_and_think(philo);
	}
	return (NULL);	
}
