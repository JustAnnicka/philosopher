/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/02 19:43:56 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

 
void	task_eat(t_table *table, t_philo *philo)
{
	struct timeval time;

	time = *table->time;
	//need funtionality if there is only one philospher
	// do the prints in the function to save space and initialisations
	pthread_mutex_lock(&philo->plock);
	philo->eat = false;
	pthread_mutex_lock(&philo->pickup);
	philo->forks = false;
	printf("%s%ld %ld has taken a fork\n", WHITE, calc_time_passed(&time), philo->id);
	pthread_mutex_lock(&philo->prev->pickup);
	philo->prev->forks = false;
	printf("%s%ld %ld has taken a fork\n", WHITE, calc_time_passed(&time), philo->id);
	printf("%ld %ld is eating\n", calc_time_passed(&time), philo->id);
	usleep(table->time_to_eat);
	philo->forks = true;
	pthread_mutex_unlock(&philo->pickup);
	philo->prev->forks = true;
	pthread_mutex_unlock(&philo->prev->pickup);
	philo->time_ill_die += calc_time_passed(&time) + table->time_to_eat;
	if (table->optional_arg == true)
		philo->times_eaten++;
	philo->sleep = true;
	pthread_mutex_unlock(&philo->plock);
}

void	task_sleep(t_table *table, t_philo *philo)
{
	long unsigned int cur_time;
	struct timeval *time;

	time = table->time;
	pthread_mutex_lock(&philo->plock);
	cur_time = calc_time_passed(time);
	printf("%s%ld %ld is sleeping\n",BLUE, cur_time, philo->id);
	philo->sleep = false;
	if (cur_time + table->time_to_sleep >= philo->time_ill_die) //might need to only > check
	{
		usleep(philo->time_ill_die);
		philo->dead = true;
	}
	else 
		usleep(table->time_to_sleep);
	philo->think = true;
	pthread_mutex_unlock(&philo->plock);
}

void	task_think(t_table *table, t_philo *philo)
{
	long unsigned int cur_time;
	struct timeval *time;

	time = table->time;
	cur_time = calc_time_passed(time);
	pthread_mutex_lock(&philo->plock);
	philo->think = false;
	printf("%s%ld %ld is thinking\n",YELLOW ,cur_time, philo->id);
	if (philo->forks == true && philo->prev->forks == true)
		philo->eat = true; //kinda waanna use this as a check for my while loop so have it as true still
	pthread_mutex_unlock(&philo->plock);
	cur_time = calc_time_passed(time);
	pthread_mutex_lock(&philo->plock);
	if (cur_time >= philo->time_ill_die)
	{
		philo->time_ill_die = cur_time - (cur_time - philo->time_ill_die);
		philo->dead = true;
		//printf("%ld %ld died\n",philo->time_of_death, philo->id);
	}
	pthread_mutex_unlock(&philo->plock);
}

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->plock);
	if (philo->dead == true)
	{
		printf("%s%ld %ld died\n", RED, (philo->time_ill_die / 1000), philo->id);
		pthread_mutex_unlock(&philo->plock);
		return (0);
	}
	pthread_mutex_unlock(&philo->plock);
	return (1);
}

void	decide_first_action(t_table *table, t_philo *philo)
{
	if (table->number_of_philosophers % 2 == 0)
	{
		if (philo->id % 2 != 0)
			task_eat(table, philo);
		else
			task_sleep(table, philo);
	}
	else 
	{
		if (philo->id == table->number_of_philosophers)
			task_think(table, philo);
		else if (philo->id % 2 != 0)
			task_eat(table, philo);
		else
			task_sleep(table, philo);
	}
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
	usleep(10); // because observer started after tasks need to fix this
	//printf("philosopher %ld thread\n", i);
	//this will be the while loop where i need to check if alive and do the tasks
	decide_first_action(t, aux);
	while(!t->end && still_alive(aux))
	{
		pthread_mutex_lock(&t->lock);
		bool ended = t->end;
		pthread_mutex_unlock(&t->lock);
		if (ended)
			break ;
		 // this should be the standard (maybe no if check)
		/* if (p % 2 == 0)
			usleep(100); */
		if (aux->eat == true)
			task_eat(t, aux);
		else if (still_alive(aux) && aux->sleep == true)
			task_sleep(t, aux);
		else if (still_alive(aux) && aux->think == true)
			task_think(t, aux);
		// change the logic here to have even numbers sleep and uneven numbers check eat (unless it is the last philo)
	}
	return (table); 
}
