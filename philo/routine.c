/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:09:45 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/21 09:28:29 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


	


int	eating(t_philos *philos)
{
	pthread_mutex_lock(&philos->first_fork);
	// if (check_if_death(philos) == -1)
	// return (-1);
	print_Status(philos, "has taken a fork");
	pthread_mutex_unlock(&philos->first_fork);
	pthread_mutex_lock(&philos->second_fork);
	// if (check_if_death(philos) == -1)
	// return (-1);
	print_Status(philos, "has taken a fork");
	pthread_mutex_unlock(&philos->second_fork);
	print_Status(philos, "eating");
	usleep(philos->parmaters->time_to_eat * 1000);
	return (0);
}

void	*philos_routine(void *arg)
{
	t_philos *philos;

	philos = (t_philos *)arg;

	while (1)
	{
		eating(philos);
		print_Status(philos, "sleeping");
		usleep(philos->parmaters->time_to_eat * 1000);
		print_Status(philos, "thinking");
	}
	return (NULL);
}