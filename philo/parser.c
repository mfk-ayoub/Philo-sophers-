/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:10:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/19 05:29:45 by ayel-mou         ###   ########.fr       */
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

int check_parmaters(int ac,char **av)
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