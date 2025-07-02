
#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h> //can I use this?
#include <unistd.h> //delete me?? (using for sleep)

# define YELLOW "\033[0;93m"
# define BLUE "\033[0;96m"
# define GREEN "\033[0;32m"
# define ORANGE "\033[0;33m"
# define RED "\033[0;31m"
# define WHITE "\033[37;1m"


typedef struct s_philo
{
	long unsigned int	id;
	pthread_t			thread;
	bool				eat; //none of these are needed in theory if I do the print in the function itself
	unsigned long int	times_eaten;
	bool				forks;
	bool				sleep; //none of these are needed in theory if I do the print in the function itself
	bool				think; //none of these are needed in theory if I do the print in the function itself
	bool				dead;
	unsigned long int	time_ill_die; // should rename to time_ill_die
	///unsigned long int	time_of_death; redundant as it should equal time_ill_die
	pthread_mutex_t		pickup;
	pthread_mutex_t		plock;
	struct s_philo		*next;
	struct s_philo		*prev;
}	t_philo;

typedef struct s_table
{
	long unsigned int	number_of_philosophers;
	long unsigned int	time_to_die;
	long unsigned int	time_to_eat;
	long unsigned int	time_to_sleep;
	long unsigned int	number_of_times_philosophers_must_eat;
	bool				optional_arg;
	struct timeval 		*time;
	pthread_t			observer;
	pthread_mutex_t		lock;
	bool				end;
	t_philo				*philosophers;
} t_table;

//INITS
void				init_table(int argc, char **argv, t_table *t);
struct timeval		*init_time(void);
void				init_threads(t_table *t);

//OBSERVER
void*				start_observing(void *table);
int					is_everyone_alive(t_table *table);

//TAKS
void* 				start_a_task(void *table);

//UTILS
int					ft_check_arguments(char **argv);
int					ft_check_valid_arguments(int argc, t_table *table); //gets called in main does not need to be in here anymore
long unsigned int	ft_atoi_long(char *argv);
int					ft_is_digit(char *argv);
void				clear_philo_lst(t_philo **philolst, long unsigned int size);
unsigned long int	calc_time_passed(struct timeval *start);

//DELETE ME LATER
void				print_table_info(t_table *table);

#endif // PHILO_H
