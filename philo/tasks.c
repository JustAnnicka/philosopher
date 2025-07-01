/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/01 12:13:13 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NEED TO USE MUTEX FOR ALL RESOURCES THAT A THREAD IS ACCESING 

/* void	observe_philosophers(t_table *table)
{
	
} */

void	task_eat(t_table *table, t_philo *philo)
{
	long unsigned int	time; // maybe use the time_till_death variable in the philo structure

	time = 0;
	//while (philo->forks == false || philo->prev->forks == false)
	while (philo->prev->pickup == true || philo->next->pickup == true)
	{
		usleep(10);
		time += 10;
		if (time >= table->time_to_die)
		{
			philo->dead = true; //set time of death 
			return ;
		}
	}
	pthread_mutex_lock(&philo->forks);
	pthread_mutex_lock(&philo->prev->forks);
//	//philo->prev->forks = false;
	//philo->forks = false;
	philo->pickup = true;
	philo->eat = true;
	usleep(table->time_to_eat);
	calculate_time_passed(table); // move this into the print thread instead
	print_thread_process(table->timestamp, philo);
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(&philo->prev->forks);
	if (table->optional_arg == true)
		philo->times_eaten++; // check this with the observer for the last philosopher
	//philo->prev->forks = true;
	//philo->forks = true;
	philo->pickup = false;
	// maybe create lock for time to die resource
	//reset time_to_die countdown
}

void	task_sleep(t_table *table, t_philo *philo)
{
	long unsigned int	time;
	
	time = table->time_to_eat;
	philo->sleep = true;
	//do a little calc for time_till_death minus time to sleep
	//check if the time_till_death is <= 0 to end programm
	usleep(table->time_to_eat);
	calculate_time_passed(table); // move this into the print thread instead
	print_thread_process(table->timestamp, philo);
	if (time >= table->time_to_die)
	{
		philo->dead = true; //set time of death 
		return ;
	}
	philo->sleep = false;
	//set sleep to true;
	//start sleeping for time_to_sleep;
	//subtract_time_to_sleep from time_till_death
	//if time_till_death is <= 0 end program
	//when sleep is done set sleep to false
}

void	task_think(t_table *table, t_philo *philo)
{
	long unsigned int	time;
	
	time = 0;
	philo->think = true;
	//while (philo->forks == false || philo->prev->forks == false)
	while (philo->prev->pickup == true || philo->next->pickup == true)
	{
		usleep(10);
		time += 10;
		if (time >= table->time_to_die)
		{
			philo->dead = true; //set time of death 
			return ;
		}
	}
	calculate_time_passed(table); // move this into the print thread instead
	print_thread_process(table->timestamp, philo);
	philo->think = false;
	//set think to true

	//subtract_time_to_think from time_till_death
	//if time_till_death is <= 0 end program
}


void*	start_a_task(void *table)
{
	static int	i;
	int			p;
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
	if (aux->prev->eat == false && aux->next->eat == false) // this should be the standard (maybe no if check)
		task_eat(t, aux);
	else if (aux->dead == false && aux->prev->eat == true)
		task_sleep(t, aux);
	else if (aux->dead == false)
		task_think(t, aux);
	return (table); 
}