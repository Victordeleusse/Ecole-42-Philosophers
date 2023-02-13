/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:17:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/13 22:12:45 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork->lock_fork));
	if (!philo->right_fork->is_used)
	{
		philo->right_fork->is_used = 1;
		philo->right_free = 1;
		pthread_mutex_unlock(&(philo->right_fork->lock_fork));
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
		pthread_mutex_unlock(&(philo->left_fork->lock_fork));
		printf("Le philosophe %d a pris sa fourchette de gauche\n", philo->philo_id);
	}
	else 
		pthread_mutex_unlock(&(philo->left_fork->lock_fork));
}

void	ft_lets_eat(t_philo *philo)
{
	if (philo->right_free && philo->left_free)
	{
		printf("Le philosophe %d est en train de manger\n", philo->philo_id);
		philo->nb_of_meal++;
		philo->last_meal = ft_get_timestamp(philo->rules->start_time);
		usleep(philo->rules->time_eat);
	}
}

void	ft_release_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork->lock_fork));
	if (philo->right_fork->is_used)
	{
		philo->right_fork->is_used = 0;
		philo->right_free = 0;
		pthread_mutex_unlock(&(philo->right_fork->lock_fork));
		printf("Le philosophe %d relache sa fourchette de droite\n", philo->philo_id);
	}
	else
		pthread_mutex_unlock(&(philo->right_fork->lock_fork));
}

void	ft_release_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->lock_fork));
	if (philo->left_fork->is_used)
	{
		philo->left_fork->is_used = 0;
		philo->left_free = 0;
		pthread_mutex_unlock(&(philo->left_fork->lock_fork));
		printf("Le philosophe %d relache sa fourchette de gauche\n", philo->philo_id);
	}
	else
		pthread_mutex_unlock(&(philo->left_fork->lock_fork));
}
