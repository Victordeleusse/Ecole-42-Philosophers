/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:31:08 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/09 11:12:22 by vde-leus         ###   ########.fr       */
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
	while (str[i] && str[i] == ' ' || str[i] == '\t')
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
	return((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}

void	msg_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}
