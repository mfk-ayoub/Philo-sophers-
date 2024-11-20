/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:37:36 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/20 05:45:37 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
		if (start_program(&parmaters,&philos) == -1)
			return (1);
		free(philos);
		free(parmaters.forks);
		return (0);
	}
	else
		return (write(2, "parmaters not valid\n", 21),1);
	return (0);
}
