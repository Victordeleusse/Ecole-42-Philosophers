/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:17:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/10 13:17:49 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork->lock_fork));
	if (!philo->right_fork->is_used)
	{
		philo->right_fork->is_used = 1;
		printf("Le philosophe %d a pris sa fourchette de droite\n", philo->philo_id);
	}
	else 
		pthread_mutex_unlock(&(philo->right_fork->lock_fork));
}

int	ft_get_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->lock_fork));
	if (!philo->left_fork->is_used)
	{
		philo->left_fork->is_used = 1;
		printf("Le philosophe %d a pris sa fourchette de gauche\n", philo->philo_id);
	}
	else 
		pthread_mutex_unlock(&(philo->left_fork->lock_fork));
}

int	ft_lets_eat(t_philo *philo)
{
	if (philo->right_free && philo->left_free)
	{
			
	}
}
