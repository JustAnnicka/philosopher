/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:45:21 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/09 17:57:01 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_table *t)
{
	long unsigned int	i;
	int					x;
	t_philo				*aux;

	i = 0;
	aux = t->philosophers;
	x = pthread_create(&t->observer, NULL, start_observing, t);
	if (x != 0)
	{
		printf("error creating observer thread \n");
		return ;
	}
	t->time = init_time();
	while (i < t->number_of_philosophers)
	{
		aux->start_time = (t->time->tv_usec / 1000) + (t->time->tv_sec * 1000);
		x = pthread_create(&aux->thread, NULL, start_a_task, t);
		i++;
		if (x != 0)
		{
			printf("error creating philosopher %ld thread \n", i);
			return ;
		}
		aux = aux->next;
	}
}

t_philo	*new_philospher(void)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = 1;
	philo->times_eaten = 0;
	philo->eat = false;
	philo->sleep = false;
	philo->fork = true;
	pthread_mutex_init(&philo->pickup, NULL);
	pthread_mutex_init(&philo->plock, NULL);
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

void	add_philosphers(t_philo *lst, t_table *table)
{
	t_philo				*aux;
	t_philo				*node;
	long unsigned int	i;

	if (!lst)
		return ;
	aux = lst;
	i = 2;
	while (i <= table->number_of_philosophers && aux)
	{
		node = new_philospher();
		if (!node)
		{
			clear_philolst(&lst, table->number_of_philosophers);
			break ;
		}
		node->id = i;
		node->time_ill_die = table->time_to_die;
		aux->next = node;
		node->prev = aux;
		aux = aux->next;
		i++;
	}
	node->next = lst;
	lst->prev = node;
}

struct timeval	*init_time(void)
{
	struct timeval	*time;
	struct timezone	timezone;

	time = (struct timeval *)malloc(sizeof(struct timeval));
	if (!time)
		return (NULL);
	gettimeofday(time, &timezone);
	return (time);
}

void	init_table(int argc, char **argv, t_table *t)
{
	t->number_of_philosophers = ft_atoi_long(argv[1]);
	t->time_to_die = ft_atoi_long(argv[2]);
	t->time_to_eat = ft_atoi_long(argv[3]);
	t->time_to_sleep = ft_atoi_long(argv[4]);
	t->optional_arg = false;
	pthread_mutex_init(&t->lock, NULL);
	pthread_mutex_init(&t->print_lock, NULL);
	t->end = false;
	if (argc == 6)
	{
		t->number_of_times_philosophers_must_eat = ft_atoi_long(argv[5]);
		t->optional_arg = true;
	}
	t->philosophers = new_philospher();
	t->philosophers->time_ill_die = t->time_to_die;
	if (t->number_of_philosophers > 1)
		add_philosphers(t->philosophers, t);
}
