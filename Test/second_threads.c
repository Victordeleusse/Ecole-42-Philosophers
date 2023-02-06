/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 23:59:00 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/05 09:58:11 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

void	*routine(void *data)
{
	pthread_t	th_id;
	int			prime;
	
	prime = *(int *)data;
	th_id = pthread_self();
	printf("Routine du thread : %d -> data : %d\n", th_id, prime);
}

int	main(int argc, char **argv)
{
	int				tab_prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	pthread_t		th[2];
	int				j = 0;
	int				*i;
	
	*i = 0;
	while (i < 2)
	{
		while (j < 5)
			pthread_create(&th[*i], NULL, &routine, &tab_prime[*i + j]);
		i++;	
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(th[i], NULL);
		printf("Execution du thread -> %d\n", i);
		i++;
	}
	return (0);	
}