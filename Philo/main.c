/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:44:10 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/21 15:18:30 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules_philo	rules;
	t_philo			*philosophes;
	t_fork			*forks;

	if (ft_init_rules(&rules, &philosophes, argc, argv))
		return (1);
	if (ft_generate_philos_forks(&philosophes, &forks, &rules))
		return (1);
	if (ft_generate_threads(&philosophes, &rules))
		return (1);
	if (ft_join_threads(&philosophes, &rules))
		return (1);
	ft_free_philos_forks(&philosophes, &forks);
	return (0);
}
