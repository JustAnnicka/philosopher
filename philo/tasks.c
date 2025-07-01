/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/01 19:14:51 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void	task_eat(t_table *table, t_philo *philo)
{
	long unsigned int cur_time;

	//need funtionality if there is only one philospher
	// redo the calc_passed_function to not use the table as this locks the whole structure
	// do the prints in the function to save space and initialisations
	pthread_mutex_lock(&philo->plock);
	pthread_mutex_lock(&philo->pickup);
	philo->fork = false;
	printf("%ld %d has taken a fork\n", calc_time_passed(table), philo->id);
	pthread_mutex_lock(&philo->prev->pickup);
	philo->prev->fork = false;
	printf("%ld %d has taken a fork\n", calc_time_passed(table), philo->id);
	philo->eat = true;
	print_thread_process(calc_time_passed(table), philo);
	usleep(table->time_to_eat);
	philo->fork = true;
	pthread_mutex_unlock(&philo->pickup);
	philo->prev->fork = true;
	pthread_mutex_unlock(&philo->prev->pickup);
	cur_time = calc_time_passed(table);
	philo->time_ill_die += cur_time;
	if (table->optional_arg == true)
		philo->times_eaten++;
	pthread_mutex_lock(&philo->plock);
} */
 
void	task_eat(t_table *table, t_philo *philo)
{
	long unsigned int cur_time;

	cur_time = calc_time_passed(table);
	//need funtionality if there is only one philospher
	// redo the calc_passed_function to not use the table as this locks the whole structure
		// -> THE WAY I AM DOING THE CURTIME IS NOT WHAT I WANT AT THE END IT SHOULD UPDATE BETWEEN EACH STEP
	// do the prints in the function to save space and initialisations
	pthread_mutex_lock(&philo->plock);
	pthread_mutex_lock(&philo->pickup);
	philo->forks = false;
	printf("%ld %d has taken a fork\n", cur_time, philo->id);
	pthread_mutex_lock(&philo->prev->pickup);
	philo->prev->forks = false;
	printf("%ld %d has taken a fork\n", cur_time, philo->id);
	printf("%ld %d is eating\n", cur_time, philo->id);
	usleep(table->time_to_eat);
	philo->forks = true;
	pthread_mutex_unlock(&philo->pickup);
	philo->prev->forks = true;
	pthread_mutex_unlock(&philo->prev->pickup);
	philo->time_ill_die += cur_time + table->time_to_eat;
	if (table->optional_arg == true)
		philo->times_eaten++;
	pthread_mutex_unlock(&philo->plock);
}

void	task_sleep(t_table *table, t_philo *philo)
{
	long unsigned int cur_time;

	cur_time = calc_time_passed(table);
	// update the get_time_passed function for a correct time measurement
	pthread_mutex_lock(&philo->plock);
	philo->sleep = true;
	printf("%ld %d is sleeping\n",cur_time, philo->id);
	usleep(table->time_to_sleep);
	if (cur_time + table->time_to_sleep >= philo->time_ill_die)
	{
		cur_time =+ table->time_to_sleep;
		philo->time_of_death = cur_time - (cur_time - philo->time_ill_die);
		philo->dead = true;
		printf("%ld %d died\n",philo->time_of_death, philo->id);
	}
	philo->sleep = false; // dont think I need these booleans as I now print inside the function
	pthread_mutex_unlock(&philo->plock);
}

void	task_think(t_table *table, t_philo *philo)
{

	long unsigned int cur_time;

	// NEED TO UPDATE HOW THE calc_time_passed function works so that i can get the actual time philo was thinking	
	pthread_mutex_lock(&philo->plock);
	philo->think = true;
	if (philo->forks == true && philo->prev->forks == true)
		philo->think = false;
	pthread_mutex_unlock(&philo->plock);
	cur_time = calc_time_passed(table);
	pthread_mutex_lock(&philo->plock);
	if (cur_time >= philo->time_ill_die)
	{
		philo->time_of_death = cur_time - (cur_time - philo->time_ill_die);
		philo->dead = true;
		printf("%ld %d died\n",philo->time_of_death, philo->id);
	}
	pthread_mutex_unlock(&philo->plock);
}

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->plock);
	if (philo->dead == true)
		return (pthread_mutex_unlock(&philo->plock), 0);
	pthread_mutex_unlock(&philo->plock);
	return (1);
}

void*	start_a_task(void *table)
{
	static int	i;
	int			p;
	int			x; // just for limiting the loop for now
	t_table		*t;
	t_philo		*aux;
	
	t = (t_table *)table;
	i++;
	aux = t->philosophers;
	p = 1;
	while (p != i)
	{
		aux = aux->next;
		p++;
	}
	//printf("philosopher %d thread\n", i);
	//this will be the while loop where i need to check if alive and do the tasks
	x = 0;
	while(still_alive(aux) && x++ < 5)
	{
		 // this should be the standard (maybe no if check)
		if (p % 2 == 0)
			usleep(10);
		task_eat(t, aux);
		if (still_alive(aux))
			task_sleep(t, aux);
		if (still_alive(aux))
			task_think(t, aux);
		// change the logic here to have even numbers sleep and uneven numbers check eat (unless it is the last philo)
	}
	return (table); 
}
