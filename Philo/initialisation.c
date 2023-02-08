/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:19:13 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/08 18:53:52 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_rules(t_rules_philo *rules, t_philo **philosophes, int argc, char **argv)
{
	int	i;
	
	i = 2;
	if (argc < 5 || argc > 6)
		msg_error(ERR_INPUT);
	if (bool_empty_false_data(argv[1]) == 0 || ft_atol(argv[1]) == 0)
		msg_error(WRONG_PHILO);
	rules->nb_must_eat = -1;
	if (argc == 6)	
	{
		if (bool_empty_false_data(argv[5]) == 0 || ft_atol(argv[5]) == 0)
			msg_error(WRONG_NB_MEALS);
		rules->nb_must_eat = (int)ft_atol(argv[5]);
	}
	while (i < 5)
	{
		if (bool_empty_false_data(argv[i])== 0 || ft_atol(argv[i]) == 0)
			msg_error(WRONG_DURATION);
		i++;	
	}
	rules->philo_nb = (int)ft_atol(argv[1]);
	rules->time_die = ft_atol(argv[2]);
	rules->time_eat = ft_atol(argv[3]);
	rules->time_slp = ft_atol(argv[4]);
	rules->philosophes = philosophes;
	rules->start_time = 0;
}

void	ft_init_philo(t_philo *philosophe, t_fork **forks, int id, t_rules_philo *rules)
{
	philosophe->philo_id = id + 1;
	philosophe->nb_of_meal = 0;
	philosophe->last_meal = 0;
	philosophe->is_dead = 0;
	philosophe->is_done = 0;
	philosophe->left_fork = &(*forks)[id];
	philosophe->left_free = 0;
	if (id == 0)
		philosophe->right_fork = &(*forks)[rules->philo_nb - 1];
	else
		philosophe->right_fork = &(*forks)[id - 1];
	philosophe->right_free = 0;
	philosophe->rules = rules;
}

void	ft_init_forks(t_fork *fork, int id)
{
	fork->fork_id = id + 1;
	fork->is_used = 0;
	pthread_mutex_init(&(fork->lock_fork), NULL);
}

void	ft_generate_philos_forks(t_philo **philosophes, t_fork **forks, t_rules_philo *rules)
{
	int	id;
	
	*philosophes = (t_philo *)malloc(sizeof(t_philo) * rules->philo_nb);
	if (!(*philosophes))
		msg_error(ERR_GEN_PHILO);
	*forks = (t_fork *)malloc(sizeof(t_fork) * rules->philo_nb);
	if (!(*forks))
	{
		free(*philosophes);
		msg_error(ERR_GEN_FORK);
	}
	id = 0;
	while (id < rules->philo_nb)
	{
		ft_init_forks(&((*forks)[id]), id);
		ft_init_philo(&((*philosophes)[id]), forks, id, rules);
		id++;
	}
}
