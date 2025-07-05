/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/02 19:43:56 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void	pickup_forks(t_table *table, t_philo *philo)
{
	unsigned long	cur_time;

	pthread_mutex_lock(&philo->pickup);
	pthread_mutex_lock(&philo->prev->pickup);
	pthread_mutex_lock(&philo->plock);
	philo->eat = false;
	//pthread_mutex_lock(&table->print_lock);
	cur_time = (calc_time_passed() - philo->start_time);
	printf("%s%ld %ld has taken a fork\n", WHITE, cur_time, philo->id);
	printf("%s%ld %ld has taken a fork\n", WHITE, cur_time, philo->id);
	printf("%ld %ld is eating\n", cur_time, philo->id);
	usleep(table->time_to_eat);
	philo->time_ill_die += ((cur_time + table->time_to_eat));
	//printf("new time ill die %ld \n", philo->time_ill_die);
	if (table->optional_arg == true)
		philo->times_eaten++;
	philo->sleep = true;
	pthread_mutex_unlock(&philo->pickup);
	pthread_mutex_unlock(&philo->prev->pickup);
	pthread_mutex_unlock(&philo->plock);
	//pthread_mutex_unlock(&table->print_lock);
} */

void	task_eat(t_table *table, t_philo *philo)
{
	unsigned long	cur_time;

	pthread_mutex_lock(&philo->pickup);
	pthread_mutex_lock(&philo->prev->pickup);
	pthread_mutex_lock(&philo->plock);
	philo->eat = false;
	pthread_mutex_lock(&table->print_lock);
	cur_time = (calc_time_passed() - philo->start_time);
	printf("%s%ld %ld has taken a fork\n", WHITE, cur_time, philo->id);
	printf("%s%ld %ld has taken a fork\n", WHITE, cur_time, philo->id);
	printf("%ld %ld is eating\n", cur_time, philo->id);
	pthread_mutex_unlock(&table->print_lock);
	usleep(table->time_to_eat);
	philo->time_ill_die += ((cur_time + table->time_to_eat));
	//printf("new time ill die %ld \n", philo->time_ill_die);
	if (table->optional_arg == true)
		philo->times_eaten++;
	//printf("%ld Times eaten: %ld\n", philo->id, philo->times_eaten);
	philo->sleep = true;
	pthread_mutex_unlock(&philo->pickup);
	pthread_mutex_unlock(&philo->prev->pickup);
	pthread_mutex_unlock(&philo->plock);

}

void	task_sleep(t_table *table, t_philo *philo)
{
	unsigned long cur_time;
	
	pthread_mutex_lock(&philo->plock);
	cur_time = (calc_time_passed() - philo->start_time);
	//pthread_mutex_lock(&table->print_lock);
	printf("%s%ld %ld is sleeping\n",BLUE, cur_time, philo->id);
	philo->sleep = false;
	if ((cur_time * 1000) + table->time_to_sleep >= philo->time_ill_die)
	{
		pthread_mutex_lock(&table->lock);
		//pthread_mutex_lock(&table->print_lock);
		cur_time *= 1000;
		usleep(philo->time_ill_die - cur_time);
		cur_time = (calc_time_passed() - philo->start_time);
		if(is_everyone_alive(table))
		{
			table->end = true;
			printf("%s%ld %ld died\n", RED, cur_time , philo->id);
			printf("sleep death time ill die %ld\n", philo->time_ill_die);
		}
	}
	else 
		usleep(table->time_to_sleep);
	pthread_mutex_unlock(&philo->plock);
	pthread_mutex_unlock(&table->lock);
}

void	task_think(t_table *table, t_philo *philo)
{
	unsigned long cur_time;
		
	pthread_mutex_lock(&philo->plock); //maye only plock if i want to write to death all other things are just reads
	pthread_mutex_lock(&table->print_lock);
	//usleep(100);
	cur_time = (calc_time_passed() - philo->start_time);
	printf("%s%ld %ld is thinking\n",YELLOW ,cur_time, philo->id);
	pthread_mutex_lock(&philo->pickup);
	pthread_mutex_lock(&philo->prev->pickup); //maybe we just need to wait till one is read rather than both (as we have the plock in task_eat)
	//if (philo->forks == true && philo->prev->forks == true)
	philo->eat = true;
	pthread_mutex_unlock(&philo->pickup);
	pthread_mutex_unlock(&philo->prev->pickup);
	cur_time = (calc_time_passed() - philo->start_time);
	//pthread_mutex_lock(&table->lock);
	if (cur_time >= philo->time_ill_die)
	{
		pthread_mutex_lock(&table->lock);
		cur_time = (calc_time_passed() - philo->start_time);
		if(is_everyone_alive(table))
		{
			table->end = true;
			printf("%s%ld %ld died\n", RED, cur_time , philo->id);
			printf("think death time ill die %ld\n", philo->time_ill_die);
		}
		//table->end = true;
	//	philo->time_ill_die = cur_time - (cur_time - philo->time_ill_die); //maybe this calculation is giving me the weird numbers?
		//printf("%s%ld %ld died\n", RED, (philo->time_ill_die / 1000), philo->id);
		//printf("think death acutal time %ld\n", calc_time_passed(&philo->start_time));
		//pthread_mutex_unlock(&philo->plock);
		//pthread_mutex_unlock(&table->print_lock);
		//	return ;
		//philo->dead = true;
		//printf("%ld %ld died\n",philo->time_of_death, philo->id);
	}
	pthread_mutex_unlock(&philo->plock);
	pthread_mutex_unlock(&table->print_lock);
	pthread_mutex_unlock(&table->lock);
	//pthread_mutex_unlock(&table->print_lock);
}

void	decide_first_action(t_table *table, t_philo *philo)
{
	if (table->number_of_philosophers == 1)
	{
		printf("%s%ld %ld has taken a fork\n", WHITE, (calc_time_passed() - philo->start_time), philo->id);
		pthread_mutex_lock(&table->lock);
		usleep(table->time_to_die);
		printf("%s%ld %ld died\n", RED, (calc_time_passed() - philo->start_time), philo->id);
		table->end = true;
		pthread_mutex_unlock(&table->lock);
	}
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

int	ate_all_meals(t_table *table, t_philo *philo)
{
	if (table->optional_arg == true)
	{
		if (philo->times_eaten >= table->number_of_times_philosophers_must_eat)
			return (1);
	}
	return (0);
}
void*	start_a_task(void *table)
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
	//usleep(100); //currently have this as I had death coinciding or a thread having started before a death was registered (resulting in an extra print)
	while(is_everyone_alive(t) && !ate_all_meals(t, aux))
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
