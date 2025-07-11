/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:46:54 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/11 20:53:28 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define YELLOW "\033[0;93m"
# define BLUE "\033[0;96m"
# define GREEN "\033[0;32m"
# define ORANGE "\033[0;33m"
# define RED "\033[0;31m"
# define WHITE "\033[0;1m"

typedef struct s_philo
{
	long unsigned int	id;
	pthread_t			thread;
	bool				eat;
	unsigned long int	times_eaten;
	bool				sleep;
	unsigned long int	time_ill_die;
	pthread_mutex_t		pickup;
	bool				fork;
	pthread_mutex_t		plock;
	unsigned long		start_time;
	struct s_philo		*next;
	struct s_philo		*prev;
}						t_philo;

typedef struct s_table
{
	long unsigned int	number_of_philosophers;
	long unsigned int	time_to_die;
	long unsigned int	time_to_eat;
	long unsigned int	time_to_sleep;
	long unsigned int	number_of_times_philosophers_must_eat;
	bool				optional_arg;
	struct timeval		*time;
	pthread_t			observer;
	pthread_mutex_t		lock;
	pthread_mutex_t		print_lock;
	bool				end;
	t_philo				*philosophers;
}						t_table;

// INITS
void					init_table(int argc, char **argv, t_table *t);
struct timeval			*init_time(void);
void					init_threads(t_table *t);

// OBSERVER
void					*start_observing(void *table);
int						is_everyone_alive(t_table *table);

// TAKS
void					decide_first_action(t_table *table, t_philo *philo);
void					*start_a_task(void *table);
void					task_eat(t_table *table, t_philo *philo);
void					task_sleep(t_table *table, t_philo *philo);
void					task_think(t_table *table, t_philo *philo);

// UTILS
int						ft_check_arguments(char **argv);
long unsigned int		ft_atoi_long(char *argv);
int						ft_is_digit(char *argv);
void					clear_philolst(t_philo **plst, long unsigned int size);
unsigned long int		calc_time_passed(void);
void					print_thread_process(t_table *table, t_philo *philo);

#endif // PHILO_H
