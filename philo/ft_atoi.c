/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:36:32 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/24 01:04:00 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int index)
{
	if ('0' <= index && '9' >= index)
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
		ans = (ans * 10) + (*str - '0');
		str++;
	}
	if (ans > INT_MAX)
		return (-1);
	return (result * ans);
}
