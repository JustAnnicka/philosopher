/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/01 17:00:20 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	task_eat(t_table *table, t_philo *philo)
{
	//if (philo->forks != 0)
	//	printf("%d %d has taken a fork\n", table->timestamp, philo->philosopher);
	//if (philo->forks->prev != 0)
	//	printf("%d %d has taken a fork\n", table->timestamp, philo->philosopher);
	while (philo->prev->eat == true || philo->next->eat == true)
	{
		usleep(10);
		philo->time_till_death -= 10;
		if (philo->time_till_death <= 0)
		{
			//pthread_mutex_lock(&table->death);
			philo->dead = true; //set time of death 
			return ;
		}
		table->timestamp = calculate_time_passed(table);
	} //can we adjust this with the mutex wait time?? calc is still alive function
	//pthread_mutex_lock(&table->eating);
	pthread_mutex_lock(&philo->forks);
	printf("%d %d has taken a fork\n", table->timestamp, philo->philosopher);
	pthread_mutex_lock(&philo->prev->forks);
	printf("%d %d has taken a fork\n", table->timestamp, philo->philosopher);
	philo->eat = true;
	print_thread_process(table, philo);
	usleep(table->time_to_eat);
	philo->time_till_death = table->time_to_die;
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_unlock(&philo->prev->forks);
	//pthread_mutex_unlock(&table->eating);
	if (table->optional_arg == true)
		philo->times_eaten++; //check this with the observer for the last philosopher
	//maybe create lock for time to die resource
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
	print_thread_process(table, philo);
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
	while (philo->prev->eat == true || philo->next->eat == true)
	{
		usleep(10);
		time += 10;
		if (time >= table->time_to_die)
		{
			philo->dead = true; //set time of death 
			return ;
		}
	} 
	print_thread_process(table, philo);
	/* if (philo->forks) // is this the same as the wait before?
		philo->think = false; */
	//subtract_time_to_think from time_till_death
	//if time_till_death is <= 0 end program
}

int	still_alive(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->death);
	if (philo->dead == true)
		return (pthread_mutex_unlock(&table->death), 0);
	pthread_mutex_unlock(&table->death);
	return (0);
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
	p = 0;
	while(still_alive(table, aux))
	{
		if (aux->prev->eat == false && aux->next->eat == false) // this should be the standard (maybe no if check)
			task_eat(t, aux);
		if (aux->dead == false && aux->prev->eat == true)
			task_sleep(t, aux);
		if (aux->dead == false)
			task_think(t, aux);
	}
	
	return (table); 
}