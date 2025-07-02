/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:25:45 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/02 19:47:10 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	else if (argc == 6
		&& table->number_of_times_philosophers_must_eat == 0)
		printf("Error\nMinimum time to sleep (milliseconds) is 1\n");
	else
		return (1);
	return (0);
}

void	destroy_mutex(t_table *table)
{
	clear_philo_lst(&table->philosophers, table->number_of_philosophers);
	pthread_mutex_destroy(&table->lock);
}

void	print_table_info(t_table *table) //DELETE ME LATER FUNCTION
{
	printf("# of philos:   %lu\n", table->number_of_philosophers);
	printf("time_to_die:   %lu\n", table->time_to_die);
	printf("time_to_eat:   %lu\n", table->time_to_eat);
	printf("time_to_sleep: %lu\n", table->time_to_sleep);
	printf("optional arg:  %i\n", table->optional_arg);
	if (table->optional_arg == true)
		printf("time must eat: %lu\n",
		table->number_of_times_philosophers_must_eat);
} 

int main(int argc, char **argv)
{
	t_table	table;
	t_philo	*aux;
	long unsigned int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		printf("Error\nWrong number of arguments");
	else if (!ft_check_arguments(argv))
		printf("Error\nonly numbers allowed (numbers must be positive)");
	else
	{
		init_table(argc, argv,&table);
		if (!ft_check_valid_arguments(argc, &table))
			return (0);
		print_table_info(&table); //this will be deleted
		init_threads(&table);
		pthread_join(table.observer, NULL); //error handling
		aux = table.philosophers;
		while (i++ < table.number_of_philosophers)
		{
			pthread_join(aux->thread, NULL); //add error handling
			aux = aux->next;
		}
		destroy_mutex(&table);
		//print of the philosophers and their tasks should be handled by observer 
	}
	return (0);
}
