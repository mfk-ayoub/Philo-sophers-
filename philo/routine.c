/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:09:45 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/26 02:16:10 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_death(t_philos *philos)
{
	pthread_mutex_lock(&philos->parmaters->lock_flag);
	if (!philos->parmaters->flag)
	{
		pthread_mutex_unlock(&philos->parmaters->lock_flag);
		return (-1);
	}
	if (current_time() - philos->last_meal > philos->parmaters->time_to_die)
	{
		philos->parmaters->flag = false;
		pthread_mutex_unlock(&philos->parmaters->lock_flag);
		printf("%lld %d is died\n", current_time()
			- philos->parmaters->start_time, philos->index);
		return (-1);
	}
	pthread_mutex_unlock(&philos->parmaters->lock_flag);
	return (0);
}

int	reverse_forks(t_philos *philos)
{
	usleep(1000);
	pthread_mutex_lock(philos->second_fork);
	if (check_if_death(philos) == -1)
		return (pthread_mutex_unlock(philos->second_fork), -1);
	print_status(philos, "has taken a fork");
	pthread_mutex_lock(philos->first_fork);
	if (check_if_death(philos) == -1)
	{
		pthread_mutex_unlock(philos->first_fork);
		return (pthread_mutex_unlock(philos->second_fork), -1);
	}
	return (0);
}

int	take_forks(t_philos *philos)
{
	if (philos->index % 2 == 1)
	{
		if (reverse_forks(philos) == -1)
			return (-1);
	}
	else
	{
		pthread_mutex_lock(philos->first_fork);
		if (check_if_death(philos) == -1)
			return (pthread_mutex_unlock(philos->first_fork), -1);
		print_status(philos, "has taken a fork");
		pthread_mutex_lock(philos->second_fork);
		if (check_if_death(philos) == -1)
		{
			pthread_mutex_unlock(philos->first_fork);
			return (pthread_mutex_unlock(philos->second_fork), -1);
		}
	}
	print_status(philos, "has taken a fork");
	return (0);
}

int	eating(t_philos *philos)
{
	if (take_forks(philos) == -1)
		return (-1);
	print_status(philos, "is eating");
	philos->meals_eat++;
	philos->last_meal = current_time();
	ft_usleep(philos->parmaters->time_to_eat, philos);
	pthread_mutex_unlock(philos->first_fork);
	pthread_mutex_unlock(philos->second_fork);
	return (0);
}

void	*philos_routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		if (philos->parmaters->nb_of_meals != -1
			&& philos->meals_eat >= philos->parmaters->nb_of_meals)
			return (NULL);
		if (eating(philos) == -1)
			return (NULL);
		if (philos->parmaters->nb_of_meals != -1
			&& philos->meals_eat >= philos->parmaters->nb_of_meals)
			return (NULL);
		print_status(philos, "is sleeping");
		ft_usleep(philos->parmaters->time_to_sleep, philos);
		print_status(philos, "is thinking");
	}
	return (NULL);
}
