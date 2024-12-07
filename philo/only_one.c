/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:48:01 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/07 07:09:44 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_one_philo(t_philo *philo, t_program *program, char **av)
{
	philo->num_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->id = 1;
	philo->first_fork = &program->forks[0];
}

void	*one_routine(void *arg)
{
	t_philo	*philo;
	size_t	start_time;

	philo = (t_philo *)arg;
	start_time = current_time();
	pthread_mutex_lock(philo->first_fork);
	printf("%ld %d has taken a fork\n", current_time() - start_time, philo->id);
	usleep(philo->time_to_die * 1000);
	printf("%ld %d is dead\n", current_time() - start_time, philo->id);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

int	one_philo(t_program *program, char **av)
{
	pthread_t	id;
	t_philo		*philo;

	program->forks = malloc(sizeof(pthread_mutex_t) * 1);
	if (!program->forks)
		return (1);
	if (pthread_mutex_init(&program->forks[0], NULL))
	{
		free(program->forks);
		return (write(2, "mutex error\n", 13), 1);
	}
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (free(program->forks), 1);
	init_one_philo(philo, program, av);
	if (pthread_create(&id, NULL, one_routine, (void *)philo))
	{
		(free(philo), free(program->forks));
		return (1);
	}
	pthread_join(id, NULL);
	pthread_mutex_destroy(&program->forks[0]);
	(free(program->forks), free(philo));
	return (0);
}
