/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:37:48 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/03 14:53:47 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timesleep(long time, t_data *data)
{
	long	sleep;

	sleep = get_time_in_ms();
	while (1)
	{
		if (is_dead(data) == 1)
			break ;
		if (get_time_in_ms() - sleep >= time)
			break ;
		usleep(50);
	}
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_printf(t_data *data, t_philo *philo, char *message)
{
	long	time;

	if (!is_dead(data))
	{
		pthread_mutex_lock(&data->print);
		time = get_time_in_ms();
		printf("%lu %d %s\n", time - philo->data->start_simulation, philo->id,
			message);
		pthread_mutex_unlock(&data->print);
	}
}

void	printf_dead(t_data *data, t_philo *philo, char *message)
{
	long	time;

	pthread_mutex_lock(&data->print);
	time = get_time_in_ms();
	printf("%lu %d %s\n", time - philo->data->start_simulation, philo->id,
		message);
	pthread_mutex_unlock(&data->print);
}

void	error_exit(char *message)
{
	printf("Error\n%s\n", message);
}
