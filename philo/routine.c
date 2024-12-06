/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 07:03:38 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/06 08:47:31 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	if (!check_death(philo) && philo->max_meals != 0)
		printf("%ld %d %s\n", current_time() - philo->start_time, philo->id,
			msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	write_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	write_message(philo, "has taken a fork");
	write_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = current_time();
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->num_of_philos == 1)
	{
		write_message(philo, "has taken a fork");
		while (!check_death(philo))
			ft_usleep(100);
		return (0);
	}
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!check_death(philo))
	{
		eat(philo);
		write_message(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		write_message(philo, "is thinking");
	}
	return (0);
}
