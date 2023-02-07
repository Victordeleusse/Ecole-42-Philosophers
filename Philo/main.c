/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:44:10 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/07 18:35:20 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules_philo	rules;
	t_philo			*philosophes;
	t_fork			*forks;
	int				id = 0;
	
	ft_init_rules(&rules, &philosophes, argc, argv);
	ft_generate_philos_forks(&philosophes, &forks, &rules);
	if (ft_start_threads(&philosophes, &rules))
	{	
		free(philosophes);
		free(forks);
		return (0);
	}
	return (0);	
}
