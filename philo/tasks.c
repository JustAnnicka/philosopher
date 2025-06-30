/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:07:30 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/18 17:52:32 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NEED TO USE MUTEX FOR ALL RESOURCES THAT A THREAD IS ACCESING 

/* void	observe_philosophers(t_table *table)
{
	
} */

/* void	task_eat(t_table *table, t_philo *philo)
{
	//check if we can pick up fork
	// -> no keep checking till resource becomes available subract time passed from time till dead
	// ---> time_till_death is <= 0 end program
	// -> yes continue and set eat as true; ()
	//pick up forks
	//start eating for time_to_eat
	//if number_of_times.. arg is true add to counter
	//place down forks
	//reset time to die countdown for this philo && and set eat to false
} */

/* void	task_sleep(t_table *table, t_philo *philo)
{
	//set sleep to true;
	//start sleeping for time_to_sleep;
	//subtract_time_to_sleep from time_till_death
	//if time_till_death is <= 0 end program
	//when sleep is done set sleep to false
} */

/* void	task_think(t_table *table, t_philo *philo)
{
	//set think to true
	//start thinking for time_to_think;
	//subtract_time_to_think from time_till_death
	//if time_till_death is <= 0 end program
} */


void*	start_a_task(void *table)
{
	//(t_table *)table;
	printf("created thread\n");
	return (table); 
}