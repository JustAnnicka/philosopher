/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:22:25 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/02 19:39:50 by aehrl            ###   ########.fr       */
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
	//need to do the mutex thingy here
	pthread_mutex_lock(&table->lock);
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&aux->plock);
		if (aux->times_eaten < table->number_of_times_philosophers_must_eat)
			check = false;
		pthread_mutex_unlock(&aux->plock);
	}
	if (check == true)
		table->end = true;
	pthread_mutex_unlock(&table->lock);
}

int	is_everyone_alive(t_table *table)
{
	t_philo	*aux;
	long unsigned int	i;

	aux = table->philosophers;
	i = 0; //could also do this check with the philo number
	pthread_mutex_lock(&table->lock);
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&aux->plock);
		if (aux->dead == true)
		{
			table->end = true;
			printf("%sSOMEONE DIED\n", RED);
			return (0);
		}	
		pthread_mutex_unlock(&aux->plock);
		i++;
	}
	pthread_mutex_unlock(&aux->plock);
	pthread_mutex_unlock(&table->lock);
	return (1);
}

void*	start_observing(void *table)
{
	t_table *t;

	t = (t_table *)table;
	printf("created observer thread\n");
	while(1)
	{
		pthread_mutex_lock(&t->lock);
		is_everyone_alive(t);
		if (t->optional_arg == true)
		{
			did_everyone_eat(t);
		}
		pthread_mutex_unlock(&t->lock);
		if (t->end == true)
			break ;
	}
	pthread_mutex_unlock(&t->lock);
	printf("end of observer thread\n");
	return (table); 
}