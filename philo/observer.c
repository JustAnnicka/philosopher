/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:22:25 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/09 12:56:38 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo_philosopher(t_table *table, t_philo *philo)
{
	unsigned long	time;

	time = (calc_time_passed() - philo->start_time);
	printf("%s%ld %ld has taken a fork\n", WHITE, time, philo->id);
	pthread_mutex_lock(&table->lock);
	usleep(table->time_to_die * 1000);
	time = (calc_time_passed() - philo->start_time);
	printf("%s%ld %ld died\n", RED, time, philo->id);
	table->end = true;
	pthread_mutex_unlock(&table->lock);
}

void	decide_first_action(t_table *table, t_philo *philo)
{
	if (table->number_of_philosophers == 1)
		solo_philosopher(table, philo);
	else if (table->number_of_philosophers % 2 == 0)
	{
		if (philo->id % 2 != 0)
			task_eat(table, philo);
		else
			task_sleep(table, philo);
	}
	else
	{
		if (philo->id == table->number_of_philosophers && philo->id != 1)
			task_think(table, philo);
		else if (philo->id % 2 != 0)
			task_eat(table, philo);
		else
			task_sleep(table, philo);
	}
}

int	did_everyone_eat(t_table *table)
{
	t_philo				*aux;
	long unsigned int	i;
	bool				check;

	aux = table->philosophers;
	i = 0;
	check = true;
	while (i < table->number_of_philosophers)
	{
		if (aux->times_eaten < table->number_of_times_philosophers_must_eat)
			check = false;
		aux = aux->next;
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

void	*start_observing(void *table)
{
	t_table	*t;

	t = (t_table *)table;
	while (1)
	{
		usleep(60);
		if (t->optional_arg == true)
		{
			if (did_everyone_eat(t))
				break ;
		}
		if (t->end == true)
			break ;
	}
	return (table);
}
