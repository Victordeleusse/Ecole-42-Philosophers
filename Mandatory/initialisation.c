/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:19:13 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/06 15:36:50 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_rules(t_rules_philo *rules, int argc, char **argv)
{
	int	i;
	
	i = 2;
	if (argc != 6)
		msg_error(ERR_INPUT);
	if (bool_empty_false_data(argv[1]) == 0 || ft_atol(argv[1]) == 0)
		msg_error(WRONG_PHILO);
	if (bool_empty_false_data(argv[argc - 1]) == 0 || ft_atol(argv[argc - 1]) == 0)
		msg_error(WRONG_NB_MEALS);
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
	rules->nb_must_eat = (int)ft_atol(argv[5]);
	(long)time(&rules->start_time);
}

void	ft_init_philos_forks(t_philo **philosophes, t_fork **forks, int i, t_rules_philo *rules)
{
	
}


void	ft_generate_philos_forks(t_philo **philosophes, t_fork **forks, t_rules_philo *rules)
{
	int	i;
	
	*philosophes = (t_philo *)malloc(sizeof(t_philo) * rules->philo_nb);
	if (!(*philosophes))
		msg_error(ERR_GEN_PHILO);
	*forks = (t_fork *)malloc(sizeof(t_fork) * rules->philo_nb);
	if (!(*forks))
	{
		free(*philosophes);
		msg_error(ERR_GEN_FORK);
	}
	i = 0;
	while (i < rules->philo_nb)
	{
		ft_init_philos_forks(philosophes[i], forks, i, rules);
		i++;
	}
}