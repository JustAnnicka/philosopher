/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:30:36 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/01 19:03:45 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
• A displayed state message should not overlap with another message.
• A message announcing a philosopher’s death must be displayed within 10 ms of
*/
void	print_thread_process(unsigned long int timestamp, t_philo *philo)
{
	if (philo->eat == true)
		printf("%ld %d is eating\n",timestamp, philo->id);
	if (philo->sleep == true)
		printf("%ld %d is sleeping\n",timestamp, philo->id);
	if (philo->think == true)
		printf("%ld %d is thinking\n",timestamp, philo->id);
	if (philo->dead == true)
		printf("%ld %d died\n",timestamp, philo->id);
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
		&& table->number_of_times_philosophers_must_eat == 0)
		printf("Error\nMinimum time to sleep (milliseconds) is 1\n");
	else
		return (1);
	return (0);
}

//DELETE ME LATER FUNCTIONS

void	print_table_info(t_table *table)
{
	//t_philo *aux;
	//long unsigned int i;
	
	//i = 0;
	printf("# of philos:   %lu\n", table->number_of_philosophers);
	printf("time_to_die:   %lu\n", table->time_to_die);
	printf("time_to_eat:   %lu\n", table->time_to_eat);
	printf("time_to_sleep: %lu\n", table->time_to_sleep);
	printf("optional arg:  %i\n", table->optional_arg);
	if (table->optional_arg == true)
		printf("time must eat: %lu\n",
		table->number_of_times_philosophers_must_eat);
	//printf("timestamp:  %i\n\n\n", table->timestamp);
/*	aux = table->philosophers;
 	while(i < table->number_of_philosophers)
	{
		printf("philospher #%d\ntime %li\n---------\n", aux->philosopher, calc_time_passed(table));
		aux = aux->next;
		// sleep (1);
		i++;
	}*/
} 
