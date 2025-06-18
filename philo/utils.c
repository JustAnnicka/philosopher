/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:12:12 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/18 16:46:38 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	calculate_time_passed(t_table *table)
{
	struct timeval time;
	struct timezone timezone;
    unsigned long int	micropassed;
    unsigned long int	secpassed;

	gettimeofday(&time,&timezone);
	micropassed = time.tv_usec - table->time->tv_usec;
	secpassed = time.tv_sec - table->time->tv_sec;
	table->timestamp = (micropassed / 1000) + (secpassed * 1000);
	return (table->timestamp);
}

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
		printf("Error\nMinimum number of philosphers is 1\n");
	else if (table->time_to_die == 0)
		printf("Error\nMinimum time to die (milliseconds) is 1\n");
	else if (table->time_to_eat == 0)
		printf("Error\nMinimum time to eat (milliseconds) is 1\n");
	else if (table->time_to_sleep == 0)
		printf("Error\nMinimum time to sleep (milliseconds) is 1\n");
	else if (argc == 6
		&& table->number_of_times_each_philosopher_must_eat == 0)
		printf("Error\nMinimum time to sleep (milliseconds) is 1\n");
	else
		return (1);
	return (0);
}
