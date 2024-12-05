/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:09:45 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/05 03:55:35 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int take_forks(t_philos *philos)
{
    if (philos->index % 2 == 0)
    {   
        pthread_mutex_lock(philos->first_fork);
        print_status(philos, "has taken a fork");
        pthread_mutex_lock(philos->second_fork);
        print_status(philos, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philos->second_fork);
        print_status(philos, "has taken a fork");
        pthread_mutex_lock(philos->first_fork);
        print_status(philos, "has taken a fork");
    }
    return 0;
}

int eating(t_philos *philos)
{
    if (take_forks(philos) == -1)
        return (-1);

    pthread_mutex_lock(&philos->parmaters->eat_flag);
    philos->last_meal = current_time();
    philos->meals_eat++;
    pthread_mutex_unlock(&philos->parmaters->eat_flag);

    print_status(philos, "is eating");
    ft_usleep(philos->parmaters->time_to_eat, philos);
    pthread_mutex_unlock(philos->first_fork);
    pthread_mutex_unlock(philos->second_fork);
    return (0);
}


void *philos_routine(void *arg)
{
    t_philos *philos;
	
	philos = (t_philos *)arg;
    if (philos->index % 2 == 0)
        usleep(100);
	
    while (true)
    {	
        pthread_mutex_lock(&philos->parmaters->lock_flag);
        if (!philos->parmaters->flag)
        {
            pthread_mutex_unlock(&philos->parmaters->lock_flag);
            return (NULL);
        }
        pthread_mutex_unlock(&philos->parmaters->lock_flag);
        if (eating(philos) == -1)
            return (NULL);
        print_status(philos, "is sleeping");
        ft_usleep(philos->parmaters->time_to_sleep, philos);
        print_status(philos, "is thinking");
    }
}






