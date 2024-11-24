/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:10:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/24 05:20:52 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_all_isdigit(char *data)
{
	int	i;

	i = 0;
	if (!data)
		return (-1);
	if (data[0] == '-' || data[0] == '+')
	{
		if (!data[1])
			return (-1);
	}
	while (data[i])
	{
		if (!ft_isdigit(data[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	check_parmaters(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_all_isdigit(av[i]) == -1 || ft_atoi(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	allocate(t_parmaters *param, t_philos **philos)
{
	int	i;

	i = 0;
	*philos = (t_philos *)malloc(sizeof(t_philos) * param->nb_of_philos);
	if (!*philos)
		return (-1);
	param->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (param->nb_of_philos));
	if (!param->forks)
		return (free(*philos), -1);
	while (i < param->nb_of_philos)
	{
		if (pthread_mutex_init(&param->forks[i], NULL))
			return (write(2, "mutex error\n", 13), -1);
		i++;
	}
	if (pthread_mutex_init(&param->print_status, NULL))
		return (write(2, "mutex error\n", 13), -1);
	if (pthread_mutex_init(&param->lock_flag, NULL))
		return (write(2, "mutex error\n", 13), -1);
	return (0);
}
