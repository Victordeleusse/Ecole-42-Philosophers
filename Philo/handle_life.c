/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:55:51 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/20 19:07:47 by vde-leus         ###   ########.fr       */
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

	philo = (t_philo *)data;
	ft_odd_life(philo);
	while (!philo->is_dead && !philo->is_done)
	{
		if ((philo->philo_id % 2))
		{
			if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
				|| philo->rules->is_a_dead)
				break ;
			ft_get_right_fork(philo);
			if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
				|| philo->rules->is_a_dead)
				break ;
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
				break ;
			ft_get_right_fork(philo);
		}
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
			|| philo->rules->is_a_dead)
			break ;
		ft_lets_eat(philo);
		if (ft_check_done_philo(philo) || ft_check_death_of_a_philo(philo) \
			|| philo->rules->is_a_dead)
			break ;
		ft_lets_sleep_and_think(philo);
	}
	return (NULL);
}
