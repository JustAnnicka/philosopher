
#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h> //can I use this?
#include <unistd.h> //delete me?? (using for sleep)

typedef struct s_philo
{
	int					philosopher;
	pthread_t			thread;
	bool				eat;
	unsigned long int	times_eaten;
	pthread_mutex_t		forks; // is this redundant ?? could i not just check pickup state
	bool				pickup;
	bool				sleep;
	bool				think;
	bool				dead;
	//unsigned long int	time_till_death; Countdown for time of death 
	//unsigned long int	tod; add time of death to ensure death message displayes within 10ms of death
	struct s_philo		*next;
	struct s_philo		*prev;
}	t_philo;

typedef struct s_table
{
	long unsigned int	number_of_philosophers;
	long unsigned int	time_to_die;
	long unsigned int	time_to_eat;
	long unsigned int	time_to_sleep;
	long unsigned int	number_of_times_each_philosopher_must_eat;
	bool				optional_arg;
	struct timeval 		*time;
	int					timestamp; //probably not an int but something else
	pthread_t			observer; // need to add initialisation for this
	t_philo				*philosophers;

} t_table;


//INITS
void				init_table(int argc, char **argv, t_table *t);
struct timeval		*init_time(void);
void				init_threads(t_table *t);

//OBSERVER
void*				start_observing(void *table);

//TAKS
void* 				start_a_task(void *table);
void				print_thread_process(int timestamp, t_philo *philo);
//UTILS
int					ft_check_arguments(char **argv);
int					ft_check_valid_arguments(int argc, t_table *table);
long unsigned int	ft_atoi_long(char *argv);
int					ft_is_digit(char *argv); //might not need
void		clear_philo_lst(t_philo **philolst, long unsigned int size);
unsigned long int	calculate_time_passed(t_table *table);

//DELETE ME LATER
void				print_table_info(t_table *table);

#endif // PHILO_H
