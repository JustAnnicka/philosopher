/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:39:50 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/11 20:58:05 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

t_philo	*init_philospher(t_table *table)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->times_eaten = 0;
	philo->time_ill_die = table->time_to_die;
	return (philo);
}

t_philo **init_array_of_philosophers(t_table *t)
{
	unsigned long	i;
	t_philo			**array;

	i = 0;
	array = (t_philo **)malloc(sizeof(t_philo *) * t->number_of_philosophers);
	if (!array)
		return (NULL);
	while (i < t->number_of_philosophers)
	{
		array[i] = init_philospher(t);
		if (array[i] == NULL)
			return(clear_philo_array(array, t->number_of_philosophers), NULL);
		array[i]->id = i + 1;
		i++;
	}
	return (array);
}

void	init_table(int argc, char **argv, t_table *t)
{
	t->number_of_philosophers = ft_atoi_long(argv[1]);
	t->time_to_die = ft_atoi_long(argv[2]);
	t->time_to_eat = ft_atoi_long(argv[3]);
	t->time_to_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		t->number_of_times_philosophers_must_eat = ft_atoi_long(argv[5]);
	else
		t->number_of_times_philosophers_must_eat = 0;
	t->end = false;
}