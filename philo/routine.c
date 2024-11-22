/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:09:45 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/22 05:38:15 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_if_death(t_philos *philos)
{
    pthread_mutex_lock(&philos->parmaters->lock_flag);
    if (!philos->parmaters->flag)
    {
        pthread_mutex_unlock(&philos->parmaters->lock_flag);
        return (-1);
    }
    if (current_time() - philos->last_meal >= philos->parmaters->time_to_die)
    {
        philos->parmaters->flag = false;
        pthread_mutex_unlock(&philos->parmaters->lock_flag);
        print_Status(philos, "died");
        return (-1);
    }
    pthread_mutex_unlock(&philos->parmaters->lock_flag);
    return (0);
}
int eating(t_philos *philos)
{
    if (philos->index % 2 == 0)
        usleep(100);
    pthread_mutex_lock(&philos->first_fork);
    if (check_if_death(philos) == -1)
        return (pthread_mutex_unlock(&philos->first_fork), -1);
    print_Status(philos, "has taken a fork");
    pthread_mutex_lock(&philos->second_fork);
    if (check_if_death(philos) == -1)
    {
        pthread_mutex_unlock(&philos->first_fork);
        return (pthread_mutex_unlock(&philos->second_fork), -1);
    }
    print_Status(philos, "has taken a fork");
    print_Status(philos, "eating");
    philos->last_meal = current_time();
    usleep(philos->parmaters->time_to_eat * 1000);
    pthread_mutex_unlock(&philos->first_fork);
    pthread_mutex_unlock(&philos->second_fork);
    return (0);
}




void *philos_routine(void *arg)
{
    t_philos *philos;
	
	philos = (t_philos *)arg;
    while (1)
    {
        if (eating(philos) == -1)
            return (NULL);
        print_Status(philos, "sleeping");
        usleep(philos->parmaters->time_to_sleep * 1000);
        print_Status(philos, "thinking");
    }
    return (NULL);
}