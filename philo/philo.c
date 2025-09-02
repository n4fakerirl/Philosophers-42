/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:22:27 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/02 17:20:12 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->lastmeal);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->lastmeal);
	if (philo->data->nbr_philo == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (!is_dead(philo->data))
	{
		take_fork(philo);
		if (is_dead(philo->data) == 1)
			break ;
		eating(philo);
		if (is_dead(philo->data) == 1)
			break ;
		sleeping(philo);
		if (is_dead(philo->data) == 1)
			break ;
		thinking(philo);
	}
	while (!is_dead(philo->data) && philo->full)
		usleep(500);
	return (NULL);
}

void	data_init(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->lastmeal, NULL);
	pthread_mutex_init(&data->meal, NULL);
	data->dead = false;
	data->start_simulation = get_time_in_ms();
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (i == data->nbr_philo - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else if (data->nbr_philo != 1)
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		i++;
	}
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data_init(data);
	while (i < data->nbr_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_simulation;
		data->philo[i].nbr_meals = 0;
		data->philo[i].full = false;
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine,
				&data->philo[i]) != 0)
		{
			while (i-- > 0)
				pthread_join(data->philo[i].thread, NULL);
			return (error_exit("Creation of the thread failed."), 0);
		}
		i++;
	}
	i = 0;
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
		return (error_exit("Creation of the thread failed."), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	if (ac != 5 && ac != 6)
		return (printf("Error\nUsage: ./philo 5 400 400 400 [5]\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!parsing(av, data))
		return (free(data), 1);
	if (!create_thread(data))
		return (free(data), 1);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
	destroy_all(data);
	free(data);
}
