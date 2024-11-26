/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:48:01 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/26 02:16:31 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_routine(void *arg)
{
	t_philos	*philos;
	long long	start_time;

	start_time = current_time();
	philos = (t_philos *)arg;
	pthread_mutex_lock(philos->first_fork);
	printf("%lld %d has taken a fork\n", current_time() - start_time,
		philos->index);
	usleep(philos->parmaters->time_to_die * 1000);
	printf("%lld %d is died\n", current_time() - start_time, philos->index);
	pthread_mutex_unlock(philos->first_fork);
	return (NULL);
}

int	one_philo(t_parmaters *parmaters)
{
	pthread_t	id;
	t_philos	*philos;

	philos = malloc(sizeof(t_philos));
	if (!philos)
		return (-1);
	philos->index = 1;
	philos->parmaters = parmaters;
	parmaters->forks = malloc(sizeof(pthread_mutex_t));
	if (!parmaters->forks)
		return (free(philos), -1);
	if (pthread_mutex_init(parmaters->forks, NULL))
	{
		(free(philos), free(parmaters->forks));
		return (write(2, "mutex error\n", 13), -1);
	}
	philos->first_fork = parmaters->forks;
	pthread_create(&id, NULL, one_routine, (void *)philos);
	pthread_join(id, NULL);
	pthread_mutex_destroy(parmaters->forks);
	free(parmaters->forks);
	free(philos);
	return (0);
}
