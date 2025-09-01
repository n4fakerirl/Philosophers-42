/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:14:34 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/01 15:27:39 by ocviller         ###   ########.fr       */
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
	t_philo				philo[200];
	pthread_mutex_t		print;
	pthread_mutex_t		death;
	pthread_mutex_t		meal;
	pthread_mutex_t		lastmeal;
	pthread_t			monitor;
}						t_data;

long					get_time_in_ms(void);
int						is_dead(t_data *data);
long					ft_atol(const char *nptr);
void					error_exit(char *message, t_data *data);
int						parsing(char **av, t_data *data);

#endif