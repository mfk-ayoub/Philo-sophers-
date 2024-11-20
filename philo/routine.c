/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:09:45 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/20 07:56:42 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philos *philos)
{
	
}
void *philos_routine(void *arg)
{
    t_philos *philos;
	
	philos = (t_philos *)arg;
	while (philos->parmaters->flag)
	{
		eating(philos);
	}
	return (NULL);
}