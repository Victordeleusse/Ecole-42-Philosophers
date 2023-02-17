/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:44:10 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/17 10:31:24 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules_philo	rules;
	t_philo			*philosophes;
	t_fork			*forks;
	int				id = 0;
	// long			start;
	// long			follow;
	
	// start = ft_get_timestamp(0);
	// ft_usleep(20000);
	// follow = ft_get_timestamp(0);
	// fprintf(stderr, "start : %ld || follow : %ld\n", start, follow);
	ft_init_rules(&rules, &philosophes, argc, argv);
	ft_generate_philos_forks(&philosophes, &forks, &rules);
	ft_generate_threads(&philosophes, &rules);
	ft_join_threads(&philosophes, &rules);
	return (0);
}
