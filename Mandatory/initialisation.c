/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:19:13 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/06 18:23:50 by vde-leus         ###   ########.fr       */
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
	while (i < argc - 1)
	{
		if (bool_empty_false_data(argv[i])== 0 || ft_atol(argv[i]) == 0)
			msg_error(WRONG_DURATION);
		i++;	
	}
	rules->philo_nb = (int)ft_atol(argv[1]);
	rules->time_die = ft_atol(argv[2]);
	rules->time_eat = ft_atol(argv[3]);
	rules->time_slp = ft_atol(argv[4]);
	(long)time(&rules->start_time);
	rules->philosophes = *philosophes;
	pthread_mutex_init(&(rules->lock_rules), NULL);
}

void	ft_init_philos_forks(int id, t_rules_philo *rules)
{
	rules->philosophes[id].philo_id = id;
	rules->philosophes[id].nb_of_meal = 0;
	rules->philosophes[id].is_dead = 0;
	rules->philosophes[id].last_meal = 0;
	rules->philosophes[id].rules = rules;
	if (id == 0)
	{
		rules->philosophes[id].right_fork = rules->philosophes->
	}	
	
	
}


void	ft_generate_philos_forks(t_philo **philosophes, t_fork **forks, t_rules_philo *rules)
{
	int	id;
	
	pthread_mutex_lock(&(rules->lock_rules));
	*philosophes = (t_philo *)malloc(sizeof(t_philo) * rules->philo_nb);
	if (!(*philosophes))
		msg_error(ERR_GEN_PHILO);
	*forks = (t_fork *)malloc(sizeof(t_fork) * rules->philo_nb);
	if (!(*forks))
	{
		free(*philosophes);
		msg_error(ERR_GEN_FORK);
	}
	rules->philosophes = *philosophes;
	id = 0;
	while (id < rules->philo_nb)
	{
		ft_init_philos_forks(id, rules);
		id++;
	}
	pthread_mutex_unlock(&(rules->lock_rules));
}