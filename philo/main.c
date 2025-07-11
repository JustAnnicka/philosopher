/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:25:45 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/09 19:04:41 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_thread_process(t_table *table, t_philo *philo)
{
	unsigned long	time;
	static int		check;

	pthread_mutex_lock(&table->print_lock);
	time = calc_time_passed() - philo->start_time;
	if (table->end == true && check == 0)
	{
		printf("%s%ld %ld died\n", RED, time, philo->id);
		check = 1;
	}
	else if (philo->eat == true)
	{
		printf("%s%ld %ld has taken a fork\n", WHITE, time, philo->id);
		printf("%s%ld %ld has taken a fork\n", WHITE, time, philo->id);
		printf("%ld %ld is eating\n", time, philo->id);
	}
	else if (philo->sleep == true)
		printf("%s%ld %ld is sleeping\n", BLUE, time, philo->id);
	else
		printf("%s%ld %ld is thinking\n", YELLOW, time, philo->id);
	pthread_mutex_unlock(&table->print_lock);
}

int	ft_check_valid_arguments(int argc, t_table *table)
{
	if (table->number_of_philosophers == 0)
		printf("Error\nMinimum number of philosphers is 1\n");
	else if (table->time_to_die == 0)
		printf("Error\nMinimum time to die (milliseconds) is 1\n");
	else if (table->time_to_eat == 0)
		printf("Error\nMinimum time to eat (milliseconds) is 1\n");
	else if (table->time_to_sleep == 0)
		printf("Error\nMinimum time to sleep (milliseconds) is 1\n");
	else if (argc == 6 && table->number_of_times_philosophers_must_eat == 0)
		printf("Error\nMinimum time to sleep (milliseconds) is 1\n");
	else
		return (1);
	return (0);
}

void	destroy_mutex(t_table *table)
{
	clear_philolst(&table->philosophers, table->number_of_philosophers);
	pthread_mutex_destroy(&table->lock);
	pthread_mutex_destroy(&table->print_lock);
	free(table->time);
}

int	main(int argc, char **argv)
{
	t_table				table;
	t_philo				*aux;
	long unsigned int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		printf("Error\nWrong number of arguments");
	else if (!ft_check_arguments(argv))
		printf("Error\nonly numbers allowed (numbers must be positive)");
	else
	{
		init_table(argc, argv, &table);
		if (!ft_check_valid_arguments(argc, &table))
			return (0);
		init_threads(&table);
		pthread_join(table.observer, NULL);
		aux = table.philosophers;
		while (i++ < table.number_of_philosophers)
		{
			pthread_join(aux->thread, NULL);
			aux = aux->next;
		}
		destroy_mutex(&table);
	}
	return (0);
}
