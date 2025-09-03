/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:04:30 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/03 14:53:24 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo(t_data *data, t_philo *philo)
{
	long	current_time;
	long	last_meal_time;

	pthread_mutex_lock(&data->lastmeal);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&data->lastmeal);
	current_time = get_time_in_ms();
	if (current_time - last_meal_time >= data->time_to_die)
	{
		pthread_mutex_lock(&data->death);
		if (!data->dead)
		{
			data->dead = true;
			pthread_mutex_unlock(&data->death);
			printf_dead(data, philo, "died");
		}
		else
			pthread_mutex_unlock(&data->death);
	}
}

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->death);
	if (data->dead == true)
	{
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	pthread_mutex_unlock(&data->death);
	return (0);
}

int	must_eat(t_data *data)
{
	int	full_count;

	full_count = 0;
	pthread_mutex_lock(&data->meal);
	full_count = data->all_full;
	pthread_mutex_unlock(&data->meal);
	if (full_count >= data->nbr_philo)
	{
		pthread_mutex_lock(&data->death);
		data->dead = true;
		pthread_mutex_unlock(&data->death);
		return (0);
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (!is_dead(data))
	{
		i = 0;
		while (i < data->nbr_philo && !is_dead(data))
		{
			check_philo(data, &data->philo[i]);
			if (is_dead(data))
				break ;
			i++;
		}
		if (data->must_eat != -1)
		{
			if (!must_eat(data))
				break ;
		}
		usleep(1000);
	}
	return (NULL);
}
