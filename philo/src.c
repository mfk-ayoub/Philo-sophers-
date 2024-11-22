/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:44:56 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/22 05:29:36 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void print_Status(t_philos *philos, char *msg)
{
    pthread_mutex_lock(&philos->parmaters->print_status);
    if (philos->parmaters->flag)
        printf("%lld %d %s\n", current_time() - philos->parmaters->start_time, philos->index, msg);
    pthread_mutex_unlock(&philos->parmaters->print_status);
}