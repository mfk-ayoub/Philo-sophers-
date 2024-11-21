/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:37:36 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/21 10:11:56 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void kill_program(t_parmaters *parmaters,t_philos *philos)
{
	int i;

	i = -1;
	while (++i < parmaters->nb_of_philos)
		pthread_mutex_destroy(&parmaters->forks[i]);
	pthread_mutex_destroy(&philos->first_fork);
	pthread_mutex_destroy(&philos->second_fork);
	pthread_mutex_destroy(&parmaters->print_status);
	pthread_mutex_destroy(&parmaters->lock_flag);
	free(philos);
}

int	main(int ac, char **av)
{
	t_parmaters parmaters;
	t_philos	*philos;
	
	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (check_parmaters(ac,av) == -1)
			return (write(2, "parmaters not valid\n", 21),1);
		init_parmaters(&parmaters, ac, av);
		if (parmaters.nb_of_philos == 1)
			return (one_philo(&parmaters));
		if (start_program(&parmaters,&philos) == -1)
			return (1);
		if (run_program(&parmaters,philos) == -1)
			return (1);
		kill_program(&parmaters,philos);
		return (0);
	}
	else
		return (write(2, "parmaters not valid\n", 21),1);
	return (0);
}
