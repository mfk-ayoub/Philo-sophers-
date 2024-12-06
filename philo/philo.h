/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 07:03:32 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/12/06 08:48:22 by ayel-mou         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				max_meals;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_program;

size_t				current_time(void);
void				ft_usleep(int n);
long long			ft_atoi(char *str);
void				init_program(char **av, t_program *pro, t_philo **philos);
void				init_philos(t_philo *philos, char **argv,
						t_program *program);
void				*routine(void *ph);
int					monitoring(t_program *data);
void				write_message(t_philo *philo, char *msg);
int					check_death(t_philo *philo);
int					check_all_ates(t_philo *philos);
void				update_flag(t_program *data, int i, int dead);
void				destroy_all(t_program *data);
int					check_parmaters(int ac, char **av);

#endif