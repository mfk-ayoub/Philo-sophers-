/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parma.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:09:59 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/20 05:45:16 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_parmaters(t_parmaters *parmaters, int ac, char **av)
{
	parmaters->nb_of_philos = ft_atoi(av[1]);
	parmaters->time_to_die = ft_atoi(av[2]);
	parmaters->time_to_eat = ft_atoi(av[3]);
	parmaters->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		parmaters->nb_of_meals = ft_atoi(av[5]);
	else
		parmaters->nb_of_meals = -1;
}

int allocate(t_parmaters *parmaters,t_philos **philos)
{
	*philos = (t_philos *)malloc(sizeof(t_philos) * parmaters->nb_of_philos);
	if (!*philos)
		return (-1);
	parmaters->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * parmaters->nb_of_philos);
    if (!parmaters->forks)
		return (free(*philos),-1);
	return (0);
}

int	start_program(t_parmaters *parmaters,t_philos **philos)
{
	int			i;

	i = 0;
	if (allocate(parmaters,philos) == -1)
		return (write(2, "alloction errors\n", 18), -1);
	while (i < parmaters->nb_of_meals)
	{
		if (!!pthread_mutex_init(&parmaters->forks[i], NULL))
			return (write(2, "mutex error\n", 13), -1);
		i++;
	}
	i = 0;
	while (i < parmaters->nb_of_philos)
    {
        (*philos)[i].index = i + 1;
        (*philos)[i].meals_eat = 0;
        (*philos)[i].parmaters = parmaters;
        (*philos)[i].r_fork = parmaters->forks[i];
        (*philos)[i].l_fork = parmaters->forks[(i + 1) % parmaters->nb_of_philos];
        i++;
    }
	return (0);
}
