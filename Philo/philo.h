/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:44:45 by vde-leus          #+#    #+#             */
/*   Updated: 2023/02/10 13:13:44 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include <time.h>
# include <sys/time.h>
# include <sys/wait.h>

#define GREEN	"\e[32m"
#define RED	"\e[31m"

# define ERR_INPUT "Please, use it as : ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_GEN_PHILO "An error as occured when generation philosopher\n"
# define ERR_GEN_FORK "An error as occured when generation philosopher\n"
# define WRONG_DURATION "Wrong entry parameter : please enter a valid duration\n"
# define WRONG_PHILO "Wrong entry parameter : please enter a valid number of philosophers\n"
# define WRONG_NB_MEALS "Wrong entry parameter : please enter a valid number of meals\n"

typedef struct s_fork
{
	int				fork_id;
	int				is_used;
	pthread_mutex_t	lock_fork;
}t_fork;

struct s_philo;

typedef struct s_rules_philo
{
	pthread_t		death_check;
	long			start_time;
	int				philo_nb;
	int				one_dead;
	long			time_die;
	long			time_eat;
	long			time_slp;
	long			time_thk;
	int				nb_must_eat;
	struct s_philo	**philosophes;
}t_rules_philo;

typedef struct s_philo
{
	pthread_t				thread_id;
	int						philo_id;
	int						nb_of_meal;
	long					last_meal;
	int						is_dead;
	int						is_done;
	struct s_fork			*left_fork;
	struct s_fork			*right_fork;
	struct s_rules_philo	*rules;
}t_philo;

int		bool_empty_false_data(char *str);
int		ft_strlen(char *str);
long	ft_atol(char *str);
long	ft_get_timestamp(long start_time);

void	msg_error(char *str);

int		ft_check_dead_or_done(t_philo *philo);
int		ft_check_global(t_philo **philosophes);

void	*ft_death(void *data);
void	*ft_life_philo(void *data);
int		ft_start_threads(t_philo **philosophes, t_rules_philo *rules);

void	ft_init_rules(t_rules_philo *rules, t_philo **philosophes, int argc, char **argv);
void	ft_init_philo(t_philo *philosophe, t_fork **forks, int id, t_rules_philo *rules);
void	ft_generate_philos_forks(t_philo **philosophes, t_fork **forks, t_rules_philo *rules);




#endif