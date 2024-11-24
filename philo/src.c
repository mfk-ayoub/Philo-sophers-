/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:44:56 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/24 05:26:59 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	print_status(t_philos *philos, char *msg)
{
	long long	time_now;

	time_now = current_time() - philos->parmaters->start_time;
	pthread_mutex_lock(&philos->parmaters->print_status);
	pthread_mutex_lock(&philos->parmaters->lock_flag);
	if (philos->parmaters->flag)
		printf(ORANGE "%lld" RESET " %d %s\n", time_now, philos->index, msg);
	pthread_mutex_unlock(&philos->parmaters->print_status);
	pthread_mutex_unlock(&philos->parmaters->lock_flag);
}

void	ft_usleep(long sleeping_time, t_philos *philos)
{
	long	start_time;

	start_time = current_time();
	while (current_time() - start_time < sleeping_time)
	{
		if (check_if_death(philos) == -1)
			break ;
		usleep(sleeping_time / 10000);
	}
}
