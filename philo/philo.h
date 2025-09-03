/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:14:34 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/03 17:26:09 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long				last_meal;
	int					nbr_meals;
	bool				full;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
	pthread_t			thread;
}						t_philo;

typedef struct s_data
{
	int					nbr_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_think;
	int					must_eat;
	long				start_simulation;
	bool				dead;
	int					all_full;
	t_philo				philo[200];
	pthread_mutex_t		print;
	pthread_mutex_t		death;
	pthread_mutex_t		meal;
	pthread_mutex_t		lastmeal;
	pthread_t			monitor;
}						t_data;

void					thinking(t_philo *philo);
void					one_philo(t_philo *philo);
void					destroy_all(t_data *data);
void					sleeping(t_philo *philo);
void					eating(t_philo *philo);
int						take_fork(t_philo *philo);
long					ft_atol(const char *nptr);
void					error_exit(char *message);
int						parsing(char **av, t_data *data);
int						parsing2(char **av, t_data *data);
int						check_args(char *av);
int						ft_isdigit(char c);
void					printf_dead(t_data *data, t_philo *philo,
							char *message);
void					safe_printf(t_data *data, t_philo *philo,
							char *message);
long					get_time_in_ms(void);
void					timesleep(long time, t_data *data);
void					check_philo(t_data *data, t_philo *philo);
int						is_dead(t_data *data);
void					*monitor_routine(void *arg);

#endif