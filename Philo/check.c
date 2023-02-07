/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:41:00 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/07 17:35:46 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_dead_or_done(t_philo *philo)
{
	if (philo->is_dead || philo->is_done)
		return (1);
	return (0); 
}

int	ft_check_global(t_philo **philosophes)
{
	int	id;

	id = 0;
	while (id < (*philosophes)->rules->philo_nb)
	{
		if ((*philosophes)[id].is_dead)
			return (1);
		id++;
	}
	return (0);
}
