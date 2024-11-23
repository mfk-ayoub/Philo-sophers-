/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:09:45 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/23 10:33:13 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_usleep(long sleeping_time, t_philos *philos)
{
	long	start_time;

	start_time = current_time();
	while (current_time() - start_time < sleeping_time)
    {
        if (check_if_death(philos) == -1)
            break;
		usleep(sleeping_time / 10000);
    }
}
int check_if_death(t_philos *philos)
{
    pthread_mutex_lock(&philos->parmaters->lock_flag);
    //printf("philo: %d, address: %p\n", philos->index, &philos->parmaters->lock_flag);
    if (!philos->parmaters->flag)
    {
        pthread_mutex_unlock(&philos->parmaters->lock_flag);
        return (-1);
    }
  /*printf("l = %lld\n c - l = %lld\n t_d = %ld\n", philos->last_meal, current_time() - philos->last_meal, philos->parmaters->time_to_die);*/
    if (current_time() - philos->last_meal > philos->parmaters->time_to_die)
    {
        philos->parmaters->flag = false;
        pthread_mutex_unlock(&philos->parmaters->lock_flag);
        printf("%lld %d died\n", current_time() - philos->parmaters->start_time, philos->index);
        return (-1);
    }
    pthread_mutex_unlock(&philos->parmaters->lock_flag);
    return (0);
}
int eating(t_philos *philos)
{
    if (philos->index % 2 == 1)
    {
        usleep(100);
        pthread_mutex_lock(philos->second_fork);
        if (check_if_death(philos) == -1)
        return (pthread_mutex_unlock(philos->second_fork), -1);
        print_Status(philos, "has taken a fork");
        pthread_mutex_lock(philos->first_fork);
        if (check_if_death(philos) == -1)
        {
            pthread_mutex_unlock(philos->first_fork);
            return (pthread_mutex_unlock(philos->second_fork), -1);
        }
        print_Status(philos, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philos->first_fork);
        if (check_if_death(philos) == -1)
            return (pthread_mutex_unlock(philos->first_fork), -1);
        print_Status(philos, "has taken a fork");
        pthread_mutex_lock(philos->second_fork);
        if (check_if_death(philos) == -1)
        {
            pthread_mutex_unlock(philos->first_fork);
            return (pthread_mutex_unlock(philos->second_fork), -1);
        }
        print_Status(philos, "has taken a fork");
    }
    print_Status(philos, "eating");
    philos->meals_eat++;
    philos->last_meal = current_time();
    ft_usleep(philos->parmaters->time_to_eat,philos);
    pthread_mutex_unlock(philos->first_fork);
    pthread_mutex_unlock(philos->second_fork);
    return (0);
}




void *philos_routine(void *arg)
{
    t_philos *philos;
	
	philos = (t_philos *)arg;
    while (1)
    {
        if(philos->parmaters->nb_of_meals != -1 && philos->meals_eat >= philos->parmaters->nb_of_meals)
            return(NULL);
        if (eating(philos) == -1)
            return (NULL);
        if(philos->parmaters->nb_of_meals != -1 && philos->meals_eat >= philos->parmaters->nb_of_meals)
            return(NULL);
        print_Status(philos, "sleeping");
        ft_usleep(philos->parmaters->time_to_sleep,philos);
        print_Status(philos, "thinking");
    }
    return (NULL);
}
