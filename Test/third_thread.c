/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:18:59 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/13 19:55:19 by vde-leus         ###   ########.fr       */
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
#define TIME_TO_COUNT 100

typedef struct s_counter
{
	int				count;
	pthread_mutex_t	count_mutex;
}t_counter;

void	*routine(void *data)
{
	t_counter	*counter;
	
	counter = (t_counter *)data;
	pthread_mutex_lock(&(counter->count_mutex));
	counter->count = 5;
	//pthread_mutex_unlock(&(counter->count_mutex));
	counter->count = 10;
	return (NULL);
}

void	*routine2(void *data)
{
	t_counter	*counter;
	
	counter = (t_counter *)data;
	pthread_mutex_lock(&(counter->count_mutex));
	counter->count = counter->count * 2;
	//pthread_mutex_unlock(&(counter->count_mutex));
	return (NULL);
}

int	main(void)
{
	pthread_t	tid;
	pthread_t	tid2;
	t_counter	counter;

	counter.count = 0;
	pthread_mutex_init(&counter.count_mutex, NULL);
	if (pthread_create(&tid, NULL, &routine, &counter) == 0)
		printf("Generation du thread\n");
	if (pthread_create(&tid2, NULL, &routine2, &counter) == 0)
		printf("Generation du thread 2\n");
	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);
	printf("Valeur finale du compteur : %d\n", counter.count);
}