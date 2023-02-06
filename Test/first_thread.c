/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:47:29 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/04 21:21:46 by vde-leus         ###   ########.fr       */
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


void	*ft_routine(void *data)
{
	pthread_t		tid;
	t_counter		*compteur;
	int				i;

	i = 0;
	compteur = (t_counter *)data;
	tid = pthread_self();
	pthread_mutex_lock(&compteur->count_mutex);
	printf("%sID du thread : [%ld] -> HELLO | valeur INIT du compteur : %d\n", BYELLOW, tid, *compteur);
	pthread_mutex_unlock(&compteur->count_mutex);
	while(i < TIME_TO_COUNT)
	{
		pthread_mutex_lock(&compteur->count_mutex);
		compteur->count = compteur->count + 1;
		pthread_mutex_unlock(&compteur->count_mutex);
		i++;
	}
	printf("%sID du thread : [%ld] -> HELLO | valeur FINALE du compteur : %d\n", BYELLOW, tid, *compteur);
	return (NULL);
}

void	*ft_routine2(void *data)
{
	pthread_t		tid;
	int				*compteur;
	int				i;

	i = 0;
	compteur = (int *)data;		
	sleep(3);
	tid = pthread_self();
	printf("%sID du thread sur routine 2: [%ld] -> HELLO | valeur INIT du compteur : %d\n", BYELLOW, tid, *compteur);
	while(i < TIME_TO_COUNT)
	{
		*compteur = *compteur + 1;
		i++;
	}
	printf("%sID du thread sur routine 2: [%ld] -> HELLO | valeur FINALE du compteur : %d\n", BYELLOW, tid, *compteur);
	return (NULL);
}

int	main(void)
{
	pthread_t		tid1;
	pthread_t		tid2;
	t_counter		compteur;

	compteur.count = 0;
	pthread_mutex_init(&compteur.count_mutex, NULL);
	if (pthread_create(&tid1, NULL, &ft_routine, &compteur) == 0)	
		printf("%sGeneration du premier thread : [%ld]\n", GREEN, tid1);
	if (pthread_create(&tid2, NULL, &ft_routine2, &compteur) == 0)	
		printf("%sGeneration du second thread : [%ld]\n", GREEN, tid2);
	// pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	if (compteur.count == 2 * TIME_TO_COUNT)
		printf("\n\n%sValeur du compteur : %d\n", GREEN, compteur);
	else
		printf("\n\n%sValeur du compteur : %d\n", RED, compteur);
	return (0);
}