/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:24:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/20 07:18:31 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>


typedef struct parmaters
{
	long	nb_of_philos;
	long	time_to_die;
	long	time_to_sleep;
	long	time_to_eat;
	long	nb_of_meals;
	pthread_mutex_t	*forks;
	bool	flag;
	
}			t_parmaters;

typedef struct s_philos
{
	int 		index;
	int			meals_eat;
	pthread_t	id;
	pthread_mutex_t l_fork;
	pthread_mutex_t r_fork;
	t_parmaters *parmaters;
	
} t_philos;

int			ft_isdigit(int index);
long		long ft_atoi(char *str);
int			check_parmaters(int ac,char **av);
void		init_parmaters(t_parmaters *parmaters, int ac, char **av);
int			start_program(t_parmaters *parmaters,t_philos **philos);
int			allocate(t_parmaters *parmaters,t_philos **philos);
int			run_program(t_parmaters *parmaters,t_philos *philos);
int			run_program(t_parmaters *parmaters,t_philos *philos);
void		*philos_routine(void *arg);

#endif