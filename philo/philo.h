
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
	bool				forks;
	bool				pickup;
	bool				sleep;
	bool				think;
	bool				dead;
	struct s_philo		*next;
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
	t_philo				*philosophers;

} t_table;


//INITS
void				init_table(int argc, char **argv, t_table *t);
struct timeval		*init_time(void);

//UTILS
int					ft_check_arguments(char **argv);
int					ft_check_valid_arguments(int argc, t_table *table);
long unsigned int	ft_atoi_long(char *argv);
int					ft_is_digit(char *argv); //might not need
void				clear_philo_lst(t_philo **philo_lst);
unsigned long int	calculate_time_passed(t_table *table);

//DELETE ME LATER
void			print_table_info(t_table *table);

#endif // PHILO_H
