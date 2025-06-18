/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:30:36 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/18 16:50:28 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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


/*
• A displayed state message should not overlap with another message.
• A message announcing a philosopher’s death must be displayed within 10 ms of
*/
void	print_thread_process(int timestamp, t_philo *philo)
{
	//this could maybe not show errors of the bool handle because of the else ifs
	if (philo->pickup == true)
		printf("%d %d has taken a fork\n", timestamp, philo->philosopher);
	else if (philo->eat == true)
		printf("%d %d is eating\n", timestamp, philo->philosopher);
	else if (philo->sleep == true)
		printf("%d %d is sleeping\n", timestamp, philo->philosopher);
	else if (philo->think == true)
		printf("%d %d is thinking\n", timestamp, philo->philosopher);
	else if (philo->dead == true)
		printf("%d %d died\n", timestamp, philo->philosopher);
}

//DELETE ME LATER FUNCTIONS

void	print_table_info(t_table *table)
{
	t_philo *aux;
	
	printf("# of philos:   %lu\n", table->number_of_philosophers);
	printf("time_to_die:   %lu\n", table->time_to_die);
	printf("time_to_eat:   %lu\n", table->time_to_eat);
	printf("time_to_sleep: %lu\n", table->time_to_sleep);
	printf("optional arg:  %i\n", table->optional_arg);
	if (table->optional_arg == true)
		printf("time must eat: %lu\n",
		table->number_of_times_each_philosopher_must_eat);
	printf("timestamp:  %i\n\n\n", table->timestamp);
	aux = table->philosophers;
	while(aux != NULL)
	{
		printf("philospher #%d\ntime %li\n---------\n", aux->philosopher, calculate_time_passed(table));
		sleep (1);
		aux = aux->next;
	}
}