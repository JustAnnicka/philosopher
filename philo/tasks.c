/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/30 21:08:23 by aehrl            ###   ########.fr       */
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
	while (philo->forks == false || philo->prev->forks == false)
	{
		usleep(100);
		time += 100;
		if (time >= table->time_to_die)
		{
			philo->dead = true; //set time of death 
			return ;
		}
	}
	philo->pickup = true;
	philo->prev->forks = false;
	philo->forks = false;
	philo->eat = true;
	usleep(table->time_to_eat);
	calculate_time_passed(table); // move this into the print thread instead
	print_thread_process(table->timestamp, philo);
	if (table->optional_arg == true)
		philo->times_eaten++; // check this with the observer for the last philosopher
	philo->prev->forks = true;
	philo->forks = true;
	//reset time_to_die countdown

	//check if we can pick up fork
	// -> no keep checking till resource becomes available subract time passed from time till dead
	// ---> time_till_death is <= 0 end program
	// -> yes continue and set eat as true; ()
	//pick up forks
	//start eating for time_to_eat
	//if number_of_times.. arg is true add to counter
	//place down forks
	//reset time to die countdown for this philo && and set eat to false
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
	while (philo->forks == false || philo->prev->forks == false)
	{
		usleep(100);
		time += 100;
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
	if (aux->forks == true && aux->prev->forks == true) // this should be the standard (maybe no if check)
		task_eat(t, aux);
	else if (aux->dead == false && aux->prev->eat == true)
		task_sleep(t, aux);
	else if (aux->dead == false)
		task_think(t, aux);
	return (table); 
}