/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:16:06 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/07 16:48:54 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_death(void *data)
{
	t_philo	*philosophe;
	int		id;
	int		dead_philo;
	long	actual_time;
	
	philosophe = *((t_philo **)data);
	dead_philo = 0;
	while (!dead_philo)
	{
		id = 0;
		while (id < philosophe->rules->philo_nb)
		{
			if (philosophe[id].nb_of_meal >= philosophe->rules->nb_must_eat && philosophe->rules->nb_must_eat > 0)
				philosophe[id].is_done = 1;
			actual_time = ft_get_timestamp();
			if ((actual_time - philosophe[id].last_meal) > philosophe->rules->time_eat || (actual_time - philosophe[id].start_life) > philosophe->rules->time_die)
			{	
				philosophe[id].is_dead = 1;
				dead_philo = 1;
			}
			id++;
		}
	}
	// kill thread life philo -> il va falloir creer des pointeur sur chacun des thread philo
}

void	*ft_life_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start_life = ft_get_timestamp();
	while (!ft_check_dead_or_done(philo) && !ft_check_global(philo->rules->philosophes))
	{
		if (philo->left_free == 0 && philo->right_free == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			philo->left_free = 1;
			pthread_mutex_lock(philo->right_fork);
			philo->right_free = 1;
			printf("Le philosophe num %d est en train de manger\n", philo->philo_id);
			usleep(philo->rules->time_eat);
			philo->left_free = 0;
			pthread_mutex_unlock(philo->left_fork);
			philo->right_free = 0;
			pthread_mutex_unlock(philo->right_fork);
			philo->last_meal = ft_get_timestamp();
			philo->nb_of_meal++;		
			printf("Le philosophe num %d est en train de dormir\n", philo->philo_id);
			usleep(philo->rules->time_slp);
		}
		// printf("Le philosophe num %d est en train de penser\n", philo->philo_id);
	}
}

int	ft_start_threads(t_philo **philosophes, t_rules_philo *rules)
{
	int			id;

	if (pthread_create(&rules->death_check, NULL, &ft_check_death, philosophes))
	{	
		perror("Failed to create a thread\n");
		return (0);
	}
	id = 0;
	while (id < rules->philo_nb)
	{
		if (pthread_create(&((*philosophes)[id]).thread_id, NULL, &ft_life_philo, &((*philosophes)[id])))
		{	
			perror("Failed to create a thread\n");
			return (0);
		}
		id++;
	}
	return (1);
}
