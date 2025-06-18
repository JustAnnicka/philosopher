/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:45:21 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/18 16:32:35 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_philo_lst(t_philo **philolst)
{
	t_philo	*aux;

	aux = *philolst;
	while((*philolst) != NULL)
	{
		aux = (*philolst)->next;
		//free the thread
		free(*philolst);
		*philolst = aux;
	}
	free(*philolst);
	*philolst = NULL;
}

t_philo	*new_philospher(void)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)malloc(sizeof(t_philo));
	if(!philosopher)
		return (NULL);
	philosopher->philosopher = 1;
	philosopher->eat = false;
	philosopher->forks = false;
	philosopher->sleep = false;
	philosopher->think = false;
	philosopher->dead = false;
	philosopher->next = NULL;
	return (philosopher);
}

void	add_philosphers(t_philo *lst, t_table *table)
{
	t_philo					*aux;
	t_philo					*node;
	long unsigned int		i;

	if (!lst)
		return ; // do i need to double check this??
	aux = lst;
	i = 2;
	while (i <= table->number_of_philosophers && aux)
	{
		node = new_philospher();
		if (!node)
		{
			clear_philo_lst(&lst);
			break ;
		}
		node->philosopher = i;
		aux->next = node;
		aux = aux->next;
		i++;
	}
}

struct timeval	*init_time(void)
{
	struct timeval *time;
	struct timezone timezone;
    
	time = (struct timeval *)malloc(sizeof(struct timeval));
	if (!time)
		return (NULL); // error handling please in the call function
	gettimeofday(time,&timezone);
	return (time);
}

void	init_table(int argc, char **argv, t_table *t)
{
	t->number_of_philosophers = ft_atoi_long(argv[1]);
	t->time_to_die = ft_atoi_long(argv[2]);
	t->time_to_eat = ft_atoi_long(argv[3]);
	t->time_to_sleep = ft_atoi_long(argv[4]);
	t->optional_arg = false;
	t->time	= init_time();
	t->timestamp = 0;
	if (argc == 6)
	{
		t->number_of_times_each_philosopher_must_eat = ft_atoi_long(argv[5]);
		t->optional_arg = true;
	}
	t->philosophers = new_philospher();
	if (t->number_of_philosophers > 1)
		add_philosphers(t->philosophers, t);
}