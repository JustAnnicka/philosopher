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

int	did_everyone_eat(t_table *table)
{
	t_philo				*aux;
	long unsigned int	i;
	bool				check;

	aux = table->philosophers;
	i = 0; //could also do this check with the philo number
	check = true;
	while (i < table->number_of_philosophers)
	{
	//	pthread_mutex_lock(&aux->plock);
	//	pthread_mutex_lock(&table->print_lock);
		//printf("%ld Times eaten: %ld\n", aux->id, aux->times_eaten);
		if (aux->times_eaten < table->number_of_times_philosophers_must_eat)
			check = false;
		aux = aux->next;
	//	pthread_mutex_unlock(&table->print_lock);
	//	pthread_mutex_unlock(&aux->plock);
		i++;
	}
	pthread_mutex_lock(&table->lock);
	if (check == true)
		table->end = true;
	pthread_mutex_unlock(&table->lock);
	return (check);
}

int	is_everyone_alive(t_table *table)
{
	if (table->end == true)
		return (0);
	return (1);
}

void*	start_observing(void *table)
{
	t_table *t;

	t = (t_table *)table;
	printf("created observer thread\n");
	while(1)
	{
	 	if (t->optional_arg == true)
		{
			if (did_everyone_eat(t))
				break ;
		}
		if (t->end == true)
			break ;
	}
	printf("end of observer thread\n");
	return (table); 
}

//new fucking plan
//->have the philosophers lock the table when death and set the end attribute (print right then and there death message)
//-> Now the observer will lock the table to check alive (in alive function) and then unlock it (THIS CAUSED DEADLOCK)
//-> Observer will lock plock while checking the eaten state
//-> if everyone has eaten all meals we will lock the table to set end

//The new still alive function litterally just checks the table attribute (does not print)
//-> THis should ensure that the process end no matter which philospher has died and we can remove the dead boolean from the philo stru