/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:16:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/07 14:03:08 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_check_death(void *data)
{
	t_philo	**philosophes;
	int		id;
	int		is_dead;
	int		is_done;
	long	atcual_time;
	
	philosophes = (t_philo **)data;
	is_dead = 0;
	is_done = 0;
	while (!is_dead && !is_done)
	{
		id = 0;
		while (id < (*philosophes)->rules->philo_nb)
		{
			if ((*philosophes)[id].nb_of_meal >= (*philosophes)->rules->nb_must_eat && (*philosophes)->rules->nb_must_eat > 0)
				is_done = 1;
			atcual_time = get_timestamp();
			if (atcual_time - (*philosophes)[id].last_meal > (*philosophes)->rules->time_eat || atcual_time - (*philosophes)[id].start_life > (*philosophes)->rules->time_die)
				is_done = 1;
		}
	}
	// kill thread life philo 
}

void	*ft_life_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start_life = get_timestamp();
		
}

int	ft_launch_life(t_philo **philosophes, t_rules_philo *rules)
{
	int			id;

	if (pthread_create(&rules->death_check, NULL, &ft_check_death, philosophes))
		return (0);
	id = 0;
	while (id < rules->philo_nb)
	{
		if (pthread_create(&((*philosophes)[id]).thread_id, NULL, &ft_life_philo, &((*philosophes)[id])))
			return (0);
		id++;
	}
	return (1);
}