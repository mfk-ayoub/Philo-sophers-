/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parma.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:09:59 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/23 10:17:00 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_parmaters(t_parmaters *parmaters, int ac, char **av)
{
	parmaters->nb_of_philos = ft_atoi(av[1]);
	parmaters->time_to_die = ft_atoi(av[2]);
	parmaters->time_to_eat = ft_atoi(av[3]);
	parmaters->time_to_sleep = ft_atoi(av[4]);
	parmaters->flag = true;
	parmaters->start_time = current_time();
	if (ac == 6)
		parmaters->nb_of_meals = ft_atoi(av[5]);
	else
		parmaters->nb_of_meals = -1;
}

int	start_program(t_parmaters *param, t_philos **philos)
{
	int	i;

	i = 0;
	if (allocate(param, philos) == -1)
		return (write(2, "alloction errors\n", 18), -1);
	while (i < param->nb_of_philos)
	{
		(*philos)[i].index = i + 1;
		(*philos)[i].meals_eat = 0;
		(*philos)[i].parmaters = param;
		(*philos)[i].last_meal = current_time();
		(*philos)[i].first_fork = &param->forks[i];
		(*philos)[i].second_fork = &param->forks[(i + 1) % param->nb_of_philos];
		i++;
	}
	return (0);
}

int	run_program(t_parmaters *parmaters, t_philos *philos)
{
	int i;

	i = 0;
	while (i < parmaters->nb_of_philos)
	{
		if (pthread_create(&philos[i].id, NULL, philos_routine,
				(void *)&philos[i]))
			return (write(2, "thread create error\n", 21), -1);
		i++;
	}
	i = 0;
  while (i < parmaters->nb_of_philos)
	{
		if (pthread_join(philos[i].id, NULL))
			return (write(2, "join error\n", 12), -1);
		i++;
	}
	return (0);
}
