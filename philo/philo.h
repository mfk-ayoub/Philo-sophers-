/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:24:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/11/23 10:30:29 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct parmaters
{
	long			nb_of_philos;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			nb_of_meals;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_status;
	pthread_mutex_t	lock_flag;
	bool			flag;

}					t_parmaters;

typedef struct s_philos
{
	int				index;
	int				meals_eat;
	long long 		last_meal;
	pthread_t		id;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_parmaters		*parmaters;

}					t_philos;

void	ft_usleep(long sleeping_time,t_philos *philos);
int					ft_isdigit(int index);
long long			ft_atoi(char *str);
int					check_parmaters(int ac, char **av);
void				init_parmaters(t_parmaters *parmaters, int ac, char **av);
int					start_program(t_parmaters *parmaters, t_philos **philos);
int					allocate(t_parmaters *parmaters, t_philos **philos);
int					run_program(t_parmaters *parmaters, t_philos *philos);
int					run_program(t_parmaters *parmaters, t_philos *philos);
void				*philos_routine(void *arg);
long long			current_time(void);
void				print_Status(t_philos *philos, char *msg);
int					one_philo(t_parmaters *parmaters);
int					check_if_death(t_philos *philos);
#endif
