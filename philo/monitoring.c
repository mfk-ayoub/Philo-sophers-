/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 07:02:17 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/07 07:00:09 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_program *data)
{
	int		i;
	size_t	time;

	while (1)
	{
		i = 0;
		while (i < data->philos[0].num_of_philos)
		{
			pthread_mutex_lock(data->philos[i].meal_lock);
			time = current_time() - data->philos[i].last_meal;
			if ((time > data->philos[i].time_to_die
					|| check_all_ates(data->philos)) && !data->philos[i].eating)
			{
				update_flag(data, i, (time > data->philos[i].time_to_die));
				return (0);
			}
			pthread_mutex_unlock(data->philos[i].meal_lock);
			i++;
		}
	}
	return (0);
}

int	check_all_ates(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].max_meals == -1)
		return (0);
	while ((i < philos[0].num_of_philos)
		&& (philos[i].max_meals <= philos[i].meals_eaten))
		i++;
	return ((i == philos[0].num_of_philos));
}

void	update_flag(t_program *data, int i, int dead)
{
	if (dead)
		write_message(&data->philos[i], "is died");
	pthread_mutex_lock(data->philos[i].dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(data->philos[i].dead_lock);
	pthread_mutex_unlock(data->philos[i].meal_lock);
}
