/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:31:08 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/20 13:55:41 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	bool_empty_false_data(char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return(1);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	ft_atol(char *str)
{
	int		i;
	long	resultat;
	
	i = 0;
	resultat = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '+')
		i++;
	while (str[i] && '0' <= str[i] && '9' >= str[i])
	{
		resultat = 10 * resultat + str[i] - '0';
		i++;
	}
	return (resultat);
}

long	ft_get_timestamp(long start_time)
{
	struct timeval time;
     
    gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000) - start_time;
}

void	ft_usleep(long time)
{
	long	chrono;
	
	chrono = ft_get_timestamp(0);
	while (ft_get_timestamp(0) - chrono < time)
		usleep(100);
}

void	msg_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

void	ft_state_msg(char *str, t_philo *philo)
{
	long	curr_time;
	long	start_time;

	pthread_mutex_lock(&(philo->rules->lock_writing));
	start_time = philo->rules->start_time;
	curr_time = ft_get_timestamp(start_time);
	printf("%ld %d %s\n",curr_time, philo->philo_id, str);
	pthread_mutex_unlock(&(philo->rules->lock_writing));
}

void	ft_state_msg_death(char *str, t_philo *philo)
{
	long	curr_time;
	long	start_time;

	pthread_mutex_lock(&(philo->rules->lock_writing));
	start_time = philo->rules->start_time;
	curr_time = ft_get_timestamp(start_time);
	printf("%ld %d %s\n",curr_time, philo->philo_id, str);
	return ;
}

void	ft_free_philos_forks(t_philo **philosophes, t_fork **forks)
{
	pthread_mutex_destroy(&(*philosophes)->lock_is_dead);
	pthread_mutex_destroy(&(*philosophes)->lock_last_meal);
	pthread_mutex_destroy(&(*philosophes)->lock_nb_of_meal);
	pthread_mutex_destroy(&(*philosophes)->rules->lock_death);
	pthread_mutex_destroy(&(*philosophes)->rules->lock_writing);
	pthread_mutex_destroy(&(*forks)->lock_fork);
	free(*philosophes);
	free(*forks);
}
