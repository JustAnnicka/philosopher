/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:22:25 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/01 15:27:50 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	did_everyone_eat(t_table *table)
{
	t_philo				*aux;
	long unsigned int	i;
	bool				check;

	aux = table->philosophers;
	i = 0; //could also do this check with the philo number
	check = true;
	while (i < table->number_of_philosophers)
	{
		if (aux->times_eaten < table->number_of_times_philosophers_must_eat)
			check = false;
	}
	if (check == true)
		table->end = true;
}

void	is_everyone_alive(t_table *table)
{
	t_philo	*aux;
	long unsigned int	i;

	aux = table->philosophers;
	i = 0; //could also do this check with the philo number
	while (i < table->number_of_philosophers)
	{
		if (aux->dead == true)
			table->end = true;
	}
}

void*	start_observing(void *table)
{
	t_table *t;

	t = (t_table *)table;
	printf("created observer thread\n");
	while(1)
	{
		pthread_mutex_lock(&t->death);
		is_everyone_alive(t);
		if (t->optional_arg == true)
		{
			pthread_mutex_lock(&t->eating);
			did_everyone_eat(t);
			pthread_mutex_unlock(&t->eating);
		}
		pthread_mutex_lock(&t->death);
		if (t->end == true)
			break ;
	}
	return (table); 
}