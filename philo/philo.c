/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:22:27 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/22 18:01:38 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*philo_routine(void *arg)
{
	t_data	*dt;

	dt = (t_data *)arg;
}

int init_fork(t_data *data)
{
	int i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (i == data->nbr_philo - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		i++;
		data->philo[i].last_meal = get_time_in_ms();
	}
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start_simulation = get_time_in_ms();
	while (i < data->nbr_philo)
	{
		data->philo[i].id = i + 1;
		// data->philo[i].last_meal = data->start_simulation;
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine,
				&data->philo[i]) != 0)
		{
			while (i-- > 0)
				pthread_join(data->philo[i].thread, NULL);
			return (error_exit("Creation of the thread failed.", data), 0);
		}
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
		pthread_join(data->philo[i++].thread, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_data		*data;
	int			i;
	pthread_t	philo[data->nbr_philo];

	if (ac != 5 && ac != 6)
		return (printf("Error\nUsage: ./philo 5 400 400 400 [5]\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	parsing(av, data);
	if (!create_thread(data))
		return (free(data), 1);
	free(data);
}
