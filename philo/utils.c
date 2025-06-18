/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:12:12 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/12 12:16:32 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_is_digit(char *argv)
{
	int	i;

	i = 0;
	while(argv[i] != '\0')
	{
		if (argv[i] < 48 || argv[i] > 57)
			return (0);
		i++;
	}
	return(1);
}
long unsigned int	ft_atoi_long(char *argv)
{
	int				i;
	int	x;
	long unsigned int	num;
	//check max number of longunsigned int and error handle it
	i = 0;
	num = 0;
	while(argv[i] != '\0')
	{
		x = argv[i] - '0';
		num = (num * 10) + x;
		i++;
	}
	return (num);
}

int	ft_check_arguments(char **argv)
{
	int	i;
	
	i = 1;
	while(argv[i])
	{
		if (argv[i][0] == '+')
			argv[i]++; // DONT LIKE THIS
		if (!ft_is_digit(argv[i]))
			return(0);
		i++;
	}
	return (1);
}

int	ft_check_valid_arguments(int argc, t_table *table)
{
	if (table->number_of_philosophers == 0)
		printf("Error\nMinimun number of philosphers is 1\n");
	else if (table->time_to_die == 0)
		printf("Error\nMinimun time to die (milliseconds) is 1\n");
	else if (table->time_to_eat == 0)
		printf("Error\nMinimun time to eat (milliseconds) is 1\n");
	else if (table->time_to_sleep == 0)
		printf("Error\nMinimun time to sleep (milliseconds) is 1\n");
	else if (argc == 6
		&& table->number_of_times_each_philosopher_must_eat == 0)
		printf("Error\nMinimun time to sleep (milliseconds) is 1\n");
	else
		return (1);
	return (0);
}


/* Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number  


int gettimeofday(struct timeval *tv, struct timezone *tz);
*/

//void	print_thread_process(pthread_t thread, int timestamp, int philo, int task)
void	print_thread_process(int timestamp, int philo, int task)
{
	if (task == 0)
		printf("%d %d has taken a fork\n", timestamp, philo);
	else if (task == 1)
		printf("%d %d is eating\n", timestamp, philo);
	else if (task == 2)
		printf("%d %d is sleeping\n", timestamp, philo);
	else if (task == 3)
		printf("%d %d is thinking\n", timestamp, philo);
	else if (task == -1)
		printf("%d %d died\n", timestamp, philo);
}

//DELETE ME LATER FUNCTIONS
void	print_table_info(t_table *table)
{
	printf("# of philos:   %lu\n", table->number_of_philosophers);
	printf("time_to_die:   %lu\n", table->time_to_die);
	printf("time_to_eat:   %lu\n", table->time_to_eat);
	printf("time_to_sleep: %lu\n", table->time_to_sleep);
	printf("optional arg:  %i\n", table->optional_arg);
	if (table->optional_arg == true)
		printf("time must eat: %lu\n",
		table->number_of_times_each_philosopher_must_eat);
}