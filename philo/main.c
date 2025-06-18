/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:25:45 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/11 20:26:11 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
-> number_of_philosophers: The number of philosophers and also the number
of forks.
-> time_to_die (in milliseconds): If a philosopher has not started eating within
time_to_die milliseconds since their last meal or the start of the simulation,
they die.
-> time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
-> time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
-> number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies. */

void	init_table(int argc, char **argv, t_table *t)
{
	t->number_of_philosophers = ft_atoi_long(argv[1]);
	t->time_to_die = ft_atoi_long(argv[2]);
	t->time_to_eat = ft_atoi_long(argv[3]);
	t->time_to_sleep = ft_atoi_long(argv[4]);
	t->optional_arg = false;
	if (argc == 6)
	{
		t->number_of_times_each_philosopher_must_eat = ft_atoi_long(argv[5]);
		t->optional_arg = true;
	}
}
	 
int main(int argc, char **argv) 
{
	t_table	table;

	if (argc < 5 || argc > 6)
		printf("Error\nWrong number of arguments");
	else if (!ft_check_arguments(argv))
		printf("Error\nonly numbers allowed (numbers mus be positive)");
	else
	{
		init_table(argc, argv,&table);
		if (!ft_check_valid_arguments(argc, &table))
			return (0);
		print_table_info(&table);
	}
	return (0);
}
