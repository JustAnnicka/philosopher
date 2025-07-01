/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:12:12 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/01 12:13:37 by aehrl            ###   ########.fr       */
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

/* void	clear_philo_lst(t_philo **philolst)
{
	t_philo	*aux;

	aux = *philolst;
	while((*philolst) != NULL)
	{
		aux = (*philolst)->next;
		//free the thread
		free(*philolst);
		*philolst = aux;
	}
	free(*philolst);
	*philolst = NULL;
} */
void	clear_philo_lst(t_philo **philolst, long unsigned int size)
{
	t_philo	*aux;
	long unsigned int 	i;
	
	aux = *philolst;
	i = 0;
	while(i < size)
	{
		aux = (*philolst)->next;
		pthread_mutex_destroy(&aux->forks);
		free(*philolst);
		*philolst = aux;
	}
	free(*philolst);
	*philolst = NULL;
}