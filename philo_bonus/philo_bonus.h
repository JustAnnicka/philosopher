/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:00:48 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/11 20:57:58 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h> //this is for the usage of semaphores
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/wait.h>

# define YELLOW "\033[0;93m"
# define BLUE "\033[0;96m"
# define GREEN "\033[0;32m"
# define ORANGE "\033[0;33m"
# define RED "\033[0;31m"
# define WHITE "\033[0;1m"

typedef struct s_philo
{
	unsigned long	id;
	pid_t			pid;
	//int				pipefd[2]; not using pipes
	unsigned long	times_eaten;
	unsigned long	time_ill_die;
	//unsigned long		start_time; // use the one from table???
	//bool				eat; // no longer need I will just iterate the start
	//bool				sleep; // no longer need I will just iterate the start
	//pthread_t			thread; // nope now a fork (process) NEED PID
	//pthread_mutex_t		pickup; // nope 
	//pthread_mutex_t		plock; // nope 
	//struct s_philo		*next;
	//struct s_philo		*prev; //should I still list these?? no longer need to check prev
}					t_philo;

typedef struct s_table
{
	unsigned long	number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	number_of_times_philosophers_must_eat;
	//bool				optional_arg;// could just set num_must_eat to 0 if > 0 arg is true
	//struct timeval		*time; //nope will just set it as a unsigned long in philos
	//pthread_t			observer;// nope
	//pthread_mutex_t		lock;// nope
	//pthread_mutex_t		print_lock;// nope
	bool			end;
	//t_philo				*philosophers;
}					t_table;

// INIT
struct timeval	*init_time(void);
void	init_table(int argc, char **argv, t_table *t);
t_philo	*init_philospher(t_table *table);
t_philo **init_array_of_philosophers(t_table *t);

// UTILS
int						ft_check_arguments(char **argv);
long unsigned int		ft_atoi_long(char *argv);
int						ft_is_digit(char *argv);
void					clear_philo_array(t_philo **plst, long unsigned int size);
unsigned long int		calc_time_passed(void);
//void					print_thread_process(t_table *table, t_philo *philo);

#endif
