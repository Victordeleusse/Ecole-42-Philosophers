/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:19:13 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/06 15:17:32 by vde-leus         ###   ########.fr       */
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

void	ft_generate_philos(t_philo **philosophes, t_fork **forks, t_rules_philo *rules)
{
	t_philo	*new_philo;
	t_fork	*new_fork;

	new_philo = (t_philo *)malloc(sizeof(t_philo) * rules->philo_nb);
	if (!new_philo)
		msg_error(ERR_GEN_PHILO);
	
}