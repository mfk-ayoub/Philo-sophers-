/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parma.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:09:59 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/05 04:15:06 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_parmaters(t_parmaters *parmaters, int ac, char **av)
{
	parmaters->nb_of_philos = ft_atoi(av[1]);
	parmaters->time_to_die = ft_atoi(av[2]);
	parmaters->time_to_eat = ft_atoi(av[3]);
	parmaters->time_to_sleep = ft_atoi(av[4]);
	parmaters->flag = true;
	parmaters->start_time = current_time();
	if (ac == 6)
		parmaters->nb_of_meals = ft_atoi(av[5]);
	else
		parmaters->nb_of_meals = -1;
}

int start_program(t_parmaters *param, t_philos **philos)
{
    int i = 0;

    if (allocate(param, philos) == -1)
        return (write(2, "allocation errors\n", 18), -1);

    while (i < param->nb_of_philos)
    {
        (*philos)[i].index = i + 1;
        (*philos)[i].meals_eat = 0;
        (*philos)[i].parmaters = param;
        (*philos)[i].last_meal = param->start_time;
        (*philos)[i].first_fork = &param->forks[i];
        (*philos)[i].second_fork = &param->forks[(i + 1) % param->nb_of_philos];
        i++;
    }
    return (0);
}


bool check_if_death(t_parmaters *parameters, int i)
{
    pthread_mutex_lock(&parameters->lock_flag);
    
    if (current_time() - parameters->philos[i].last_meal > parameters->time_to_die)
    {
        parameters->flag = false;
        pthread_mutex_unlock(&parameters->lock_flag);
        
        printf("%lld %d is died\n",
               current_time() - parameters->start_time,
               parameters->philos[i].index);
        return (true);
    }
    pthread_mutex_unlock(&parameters->lock_flag);
    return (false);
}



bool check_all_meals_eaten(t_parmaters *parameters)
{
    bool all_meals_eaten = true;
    int i;

	i = 0;
    while (i < parameters->nb_of_philos)
    {
        pthread_mutex_lock(&parameters->lock_flag);

        if (parameters->nb_of_meals != -1 &&
            parameters->philos[i].meals_eat < parameters->nb_of_meals)
            all_meals_eaten = false;

        pthread_mutex_unlock(&parameters->lock_flag);
        i++; 
    }
    return (all_meals_eaten);
}


void *monitoring_routine(void *arg)
{
    t_parmaters *parameters;
	int i;

	parameters = (t_parmaters *)arg;
    while (1)
    {
		usleep(50);
		i = 0;
        while (i < parameters->nb_of_philos)
        {
            if (check_if_death(parameters, i))
                return (NULL);
			i++;
        }
        if (parameters->nb_of_meals != -1 && check_all_meals_eaten(parameters))
        {
            pthread_mutex_lock(&parameters->lock_flag);
            parameters->flag = false;
            pthread_mutex_unlock(&parameters->lock_flag);
            return (NULL);
        }
        usleep(1000);
    }
}


int run_program(t_parmaters *parameters, t_philos *philos)
{
    int i;
    pthread_t monitor_thread;

    i = 0;
    while (i < parameters->nb_of_philos)
    {
        if (pthread_create(&philos[i].id, NULL, philos_routine, &philos[i]))
            return (write(2, "Thread creation error\n", 23), -1);
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, monitoring_routine, parameters))
        return (write(2, "Monitor thread error\n", 22), -1);
    pthread_join(monitor_thread, NULL);
    i = 0;
    while (i < parameters->nb_of_philos)
    {
        if (pthread_join(philos[i].id, NULL))
            return (write(2, "Thread join error\n", 19), -1);
        i++;
    }
    return 0;
}





