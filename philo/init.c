/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 07:01:59 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/07 07:12:57 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(char **av, t_program *pro, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(struct s_philo) * (ft_atoi(av[1])));
	if (!*philos)
		return ;
	pro->dead_flag = 0;
	pthread_mutex_init(&pro->dead_lock, NULL);
	pthread_mutex_init(&pro->meal_lock, NULL);
	pthread_mutex_init(&pro->write_lock, NULL);
	pro->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!(*pro).forks)
		destroy_all(pro);
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&pro->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_philo *philos, char **av, t_program *program)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		philos[i].num_of_philos = ft_atoi(av[1]);
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		philos[i].max_meals = ft_atoi(av[5]);
		philos[i].start_time = current_time();
		philos[i].last_meal = current_time();
		philos[i].meals_eaten = 0;
		philos[i].eating = 0;
		philos[i].id = i + 1;
		philos[i].dead = &program->dead_flag;
		philos[i].first_fork = &program->forks[i];
		philos[i].second_fork = &program->forks[(i + 1)
			% philos[i].num_of_philos];
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
	}
}
