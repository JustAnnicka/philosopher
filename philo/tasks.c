/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/09 17:58:21 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	task_eat(t_table *table, t_philo *philo)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->pickup);
	pthread_mutex_lock(&philo->prev->pickup);
	pthread_mutex_lock(&philo->plock);
	philo->eat = true;
	philo->fork = false;
	philo->prev->fork = false;
	print_thread_process(table, philo);
	time = calc_time_passed() - philo->start_time;
	philo->time_ill_die = (time + table->time_to_die);
	usleep((table->time_to_eat * 1000));
	philo->eat = false;
	if (table->optional_arg == true)
		philo->times_eaten++;
	philo->fork = true;
	philo->prev->fork = true;
	philo->sleep = true;
	pthread_mutex_unlock(&philo->pickup);
	pthread_mutex_unlock(&philo->prev->pickup);
	pthread_mutex_unlock(&philo->plock);
}

void	task_sleep(t_table *table, t_philo *philo)
{
	unsigned long	cur_time;

	pthread_mutex_lock(&philo->plock);
	philo->sleep = true;
	print_thread_process(table, philo);
	cur_time = (calc_time_passed() - philo->start_time);
	if (cur_time + table->time_to_sleep >= philo->time_ill_die)
	{
		pthread_mutex_lock(&table->lock);
		usleep((philo->time_ill_die - cur_time) * 1000);
		cur_time = (calc_time_passed() - philo->start_time);
		if (is_everyone_alive(table))
		{
			table->end = true;
			print_thread_process(table, philo);
		}
	}
	else
		usleep(table->time_to_sleep * 1000);
	philo->sleep = false;
	pthread_mutex_unlock(&philo->plock);
	pthread_mutex_unlock(&table->lock);
}

void	task_think(t_table *table, t_philo *philo)
{
	unsigned long	cur_time;

	pthread_mutex_lock(&philo->plock);
	usleep(60);
	cur_time = (calc_time_passed() - philo->start_time);
	print_thread_process(table, philo);
	pthread_mutex_lock(&philo->pickup);
	pthread_mutex_lock(&philo->prev->pickup);
	pthread_mutex_unlock(&philo->pickup);
	pthread_mutex_unlock(&philo->prev->pickup);
	cur_time = (calc_time_passed() - philo->start_time);
	if (cur_time >= philo->time_ill_die)
	{
		cur_time = (calc_time_passed() - philo->start_time);
		if (is_everyone_alive(table))
		{
			pthread_mutex_lock(&table->lock);
			table->end = true;
			print_thread_process(table, philo);
			pthread_mutex_unlock(&table->lock);
		}
	}
	philo->eat = true;
	pthread_mutex_unlock(&philo->plock);
	pthread_mutex_unlock(&table->lock);
}

int	ate_all_meals(t_table *table, t_philo *philo)
{
	if (table->optional_arg == true)
	{
		if (philo->times_eaten >= table->number_of_times_philosophers_must_eat)
			return (1);
	}
	return (0);
}

void	*start_a_task(void *table)
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
	decide_first_action(t, aux);
	while (is_everyone_alive(t) && !ate_all_meals(t, aux))
	{
		if (aux->eat == true)
			task_eat(t, aux);
		else if (is_everyone_alive(t) && aux->sleep == true)
			task_sleep(t, aux);
		else if (is_everyone_alive(t))
			task_think(t, aux);
	}
	return (table);
}
