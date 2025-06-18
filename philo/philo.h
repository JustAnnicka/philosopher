
#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h> //can I use this?

typedef struct s_table
{
	long unsigned int	number_of_philosophers;
	long unsigned int	time_to_die;
	long unsigned int	time_to_eat;
	long unsigned int	time_to_sleep;
	long unsigned int	number_of_times_each_philosopher_must_eat;
	bool				optional_arg;
	//pthread_t			*threads; //can i make an array of threads?

} t_table;


//UTILS
int				ft_check_arguments(char **argv);
int				ft_check_valid_arguments(int argc, t_table *table);
long unsigned int	ft_atoi_long(char *argv);
int				ft_is_digit(char *argv); //might not need

//DELETE ME LATER
void			print_table_info(t_table *table);

#endif // PHILO_H
