/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:04:30 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/01 18:05:45 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_philo(t_data *data, t_philo *philo)
{
	long	current_time;
	long	meal;

	pthread_mutex_lock(&data->lastmeal);
	current_time = get_time_in_ms();
	meal = philo->last_meal;
	pthread_mutex_unlock(&data->lastmeal);
	if (get_time_in_ms() - philo->last_meal >= data->time_to_die)
	{
		pthread_mutex_lock(&data->death);
		if (!data->dead)
		{
			data->dead = true;
			printf_dead(data, philo, "died");
		}
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

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		i = 0;
		while (i < data->nbr_philo && !data->dead)
		{
			data->philo[i].data = data;
			check_philo(data, &data->philo[i]);
			if (is_dead(data) == 1)
				break ;
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
