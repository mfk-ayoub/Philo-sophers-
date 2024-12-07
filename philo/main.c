/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 07:02:09 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/07 07:10:09 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_program *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->philos)
		free(data->philos);
	if (data->philos)
		free(data->forks);
}

int	synchronization_start(t_philo *philos, t_program *program)
{
	int	i;

	i = -1;
	while (++i < philos[0].num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			return (destroy_all(program), 0);
	}
	monitoring(program);
	i = -1;
	while (++i < philos[0].num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (destroy_all(program), 0);
	}
	destroy_all(program);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		*philos;
	t_program	program;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (check_parmaters(ac, av) == -1)
			return (write(2, "Parameters not valid\n", 21), -1);
		if (ft_atoi(av[1]) == 1)
		{
			if (one_philo(&program, av))
				return (1);
			return (0);
		}
		init_program(av, &program, &philos);
		init_philos(philos, av, &program);
		program.philos = philos;
		if (synchronization_start(philos, &program) == -1)
			return (1);
	}
	else
		return (write(2, "Parameters not valid\n", 21), -1);
	return (0);
}
