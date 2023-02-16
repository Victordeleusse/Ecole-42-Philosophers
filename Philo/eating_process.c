/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:17:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/16 16:21:32 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_done_philo(t_philo *philo)
{
	int	nb_mandatory_meal;

	pthread_mutex_lock(&(philo->lock_nb_of_meal));
	nb_mandatory_meal = philo->rules->nb_must_eat;
	pthread_mutex_unlock(&(philo->lock_nb_of_meal));
	if (philo->nb_of_meal >= nb_mandatory_meal)
	{
		philo->is_done = 1;
		pthread_mutex_lock(&(philo->rules->lock_writing));
		printf("Le philosophe %d a fini de manger\n", philo->philo_id);
		pthread_mutex_unlock(&(philo->rules->lock_writing));
	}
}

void	ft_lets_sleep_and_think(t_philo *philo)
{	
	ft_check_done_philo(philo);
	if (philo->is_done)
		exit(1) ;
	pthread_mutex_lock(&(philo->rules->lock_writing));
	printf("Le philosophe %d dort\n", philo->philo_id);
	printf("Le philosophe %d pense\n", philo->philo_id);
	pthread_mutex_unlock(&(philo->rules->lock_writing));
	usleep(philo->rules->time_slp);
	usleep(philo->rules->time_thk);
}

void	ft_get_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork->lock_fork));
	if (!philo->right_fork->is_used)
	{
		philo->right_fork->is_used = 1;
		philo->right_free = 1;
		printf("Le philosophe %d a pris sa fourchette de droite\n", philo->philo_id);
	}
	else 
		pthread_mutex_unlock(&(philo->right_fork->lock_fork));
}

void	ft_get_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->lock_fork));
	if (!philo->left_fork->is_used)
	{
		philo->left_fork->is_used = 1;
		philo->left_free = 1;
		printf("Le philosophe %d a pris sa fourchette de gauche\n", philo->philo_id);
	}
	else 
		pthread_mutex_unlock(&(philo->left_fork->lock_fork));
}

void	ft_lets_eat(t_philo *philo)
{
	if (philo->right_free && philo->left_free)
	{
		pthread_mutex_lock(&(philo->rules->lock_writing));
		printf("Le philosophe %d est en train de manger\n", philo->philo_id);
		pthread_mutex_unlock(&(philo->rules->lock_writing));
		usleep(philo->rules->time_eat);
		pthread_mutex_lock(&(philo->lock_last_meal));
		philo->nb_of_meal++;
		philo->last_meal = ft_get_timestamp(philo->rules->start_time);
		pthread_mutex_unlock(&(philo->lock_last_meal));
	}
	philo->right_fork->is_used = 0;
	philo->right_free = 0;
	philo->left_fork->is_used = 0;
	philo->left_free = 0;
	pthread_mutex_unlock(&(philo->left_fork->lock_fork));
	pthread_mutex_unlock(&(philo->right_fork->lock_fork));
	pthread_mutex_lock(&(philo->rules->lock_writing));
	printf("Le philosophe %d relache sa fourchette de droite\n", philo->philo_id);
	printf("Le philosophe %d relache sa fourchette de gauche\n", philo->philo_id);
	pthread_mutex_unlock(&(philo->rules->lock_writing));
	ft_lets_sleep_and_think(philo);
}
