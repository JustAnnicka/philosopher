/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:14:44 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/11 20:56:32 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


unsigned long	calc_time_passed(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void	clear_philo_array(t_philo **array, unsigned long size)
{
	unsigned long	i;

	i = 0;
	while (i < size)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

int	ft_is_digit(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < 48 || argv[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

long unsigned int	ft_atoi_long(char *argv)
{
	int					i;
	int					x;
	long unsigned int	num;

	i = 0;
	num = 0;
	while (argv[i] != '\0')
	{
		x = argv[i] - '0';
		num = (num * 10) + x;
		i++;
	}
	return (num);
}

int	ft_check_arguments(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '+')
			argv[i]++;
		if (!ft_is_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}