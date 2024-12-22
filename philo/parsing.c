/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 07:02:21 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/22 19:15:00 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int index)
{
	if ('0' <= index && index <= '9')
		return (1);
	return (0);
}

static bool	is_space(char c)
{
	char	*str;

	str = "\t\n\v\f\r ";
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

long long	ft_atoi(char *str)
{
	long long	ans;
	long long	result;

	if (!str)
		return (-1);
	ans = 0;
	result = 1;
	while (is_space(*str))
		str++;
	if (*str == '-')
		result *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		ans = (ans * 10) + (*str - '0');
		str++;
	}
	if (ans >= INT_MAX)
		return (-1);
	return (result * ans);
}

int	ft_all_isdigit(char *data)
{
	int	i;

	i = 0;
	if (!data)
		return (-1);
	if (data[0] == '+' || data[0] == '-')
	{
		if ((data[0] == '-' || data[0] == '+') && !data[1])
			return (-1);
		if ((data[0] == '-' || data[0] == '+') && data[1])
		{
			if (data[0] == '-')
				return (-1);
		}
		i++;
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
