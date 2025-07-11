/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:12:21 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/11 21:29:48 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_table_info(t_table *table) //DELETE ME LATER FUNCTION
{
	printf("# of philos:   %lu\n", table->number_of_philosophers);
	printf("time_to_die:   %lu\n", table->time_to_die);
	printf("time_to_eat:   %lu\n", table->time_to_eat);
	printf("time_to_sleep: %lu\n", table->time_to_sleep);
	printf("time must eat: %lu\n", table->number_of_times_philosophers_must_eat);
}

//could be an int for the error handling
/* void	ft_wait(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < (px->p_count))
	{
		waitpid(px->pids[i], &px->status, 0);
		if (WIFEXITED(px->status) && px->status != 0)
			px->status = WEXITSTATUS(px->status);
		if (WIFSIGNALED(px->status) && px->status != 0)
			px->status = WTERMSIG(px->status);
		i++;
	}
} */
void	ft_wait(t_philo **philos, unsigned long size)
{
	unsigned long	i;

	i = 0;
	printf("ENTER WAiT i = %ld\n", i);
	while (i < size)
	{
		waitpid(philos[i]->pid, 0, 0);
	/* 	if (WIFEXITED(philos[i]->status) && philos[i]->status != 0)
			philos[i]->status = WEXITSTATUS(philos[i]->status);
		if (WIFSIGNALED(philos[i]->status) && philos[i]->status != 0)
			philos[i]->status = WTERMSIG(philos[i]->status); */
		i++;
	}
}
void	start_task(t_philo *philo)
{
	philo->pid = fork();
	if (philo->pid < 0)
		perror("Error\n forking process");
	if (philo->pid == 0)
	{
		printf("Philo#: %ld\n", philo->id);
		exit(0);
	}
}

int start_observing(t_table *table, t_philo **philos, sem_t *semaphore)
{	
	unsigned long	i;

	i = 0;
	semaphore = (void *)semaphore;
	while(i < table->number_of_philosophers)
	{
		start_task(philos[i]);
		i++;
	}
	//ft_wait(philos, table->number_of_philosophers);
	return (0);
	//exit(0);
	//return (0);
}

int	main(int argc, char *argv[])
{
	sem_t 			forks;
	int 			ret;
	t_table			table;
	t_philo			**philos;
	//can add a second semaphore for how many philosophers can eat at once (num of forks / 2)
	if (argc < 5 || argc > 6)
		return (printf("Error\nWrong number of arguments"), 1);
	else if (!ft_check_arguments(argv))
		return (printf("Error\nonly numbers allowed (numbers must be positive)"), 1);
	ret = sem_init(&forks, 1, ft_atoi_long(argv[1]));
	printf("number of forks: %lu\npairs of forks %d\n", ft_atoi_long(argv[1]), ret);
	init_table(argc, argv, &table);
	philos = init_array_of_philosophers(&table);
	if (philos == NULL)
		return (printf("Error\nCreating philosophers"), 1);
	print_table_info(&table);
	start_observing(&table, philos, &forks);
	ft_wait(philos, table.number_of_philosophers);
	printf("exited observer\n");
	//printf("id: %ld\n", philos[table.number_of_philosophers - 1]->id);
	return(clear_philo_array(philos, table.number_of_philosophers), 0);
}

