/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parma.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:09:59 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/19 02:15:36 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_parmaters(t_parmaters *parmaters,int ac,char **av)
{
	parmaters->nb_of_philos = ft_atoi(av[1]);
	parmaters->time_to_die = ft_atoi(av[2]);
	parmaters->time_to_eat  = ft_atoi(av[3]);
	parmaters->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		parmaters->nb_of_meals = ft_atoi(av[5]);
	parmaters->nb_of_meals = 0;
}