/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:44:10 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/18 15:52:00 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules_philo	rules;
	t_philo			*philosophes;
	t_fork			*forks;
	
	ft_init_rules(&rules, &philosophes, argc, argv);
	ft_generate_philos_forks(&philosophes, &forks, &rules);
	ft_generate_threads(&philosophes, &rules);
	ft_join_threads(&philosophes, &rules);
	return (0);
}