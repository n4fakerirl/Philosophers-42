/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:22:27 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/26 14:35:43 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_printf(t_data *data, t_philo *philo, char *message)
{
	long	time;

	pthread_mutex_lock(&data->print);
	time = get_time_in_ms();
	printf("%lu %d %s\n", time - philo->data->start_simulation, philo->id,
		message);
	pthread_mutex_unlock(&data->print);
}

void	take_fork(t_philo *philo)
{
	if (philo.)
	pthread_mutex_lock(&philo->right_fork);
	safe_printf(philo->data, philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork);
	safe_printf(philo->data, philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	safe_printf(philo->data, philo, "is eating");
	usleep(philo->data->time_to_eat);
	philo->last_meal = get_time_in_ms() + philo->data->time_to_eat;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	safe_printf(philo->data, philo, "is sleeping");
	usleep(philo->data->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(philo->data->time_to_eat);
	while (1)
	{
		if (philo->data->time_to_die < philo->data->time_to_eat)
		{
			philo->data->dead = true;
			safe_printf(philo->data, philo, "is dead");
			break ;
		}
		take_fork(philo);
		eating(philo);
		sleeping(philo);
	}
	return (arg);
}

void	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (i == data->nbr_philo - 1)
			data->philo[i].right_fork = data->philo[0].left_fork;
		else
			data->philo[i].right_fork = data->philo[i + 1].left_fork;
		i++;
	}
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start_simulation = get_time_in_ms();
	init_fork(data);
	while (i < data->nbr_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
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
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("Error\nUsage: ./philo 5 400 400 400 [5]\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!parsing(av, data))
		return (1);
	if (!create_thread(data))
		return (free(data), 1);
	free(data);
}
