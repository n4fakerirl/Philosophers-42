/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:22:27 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/01 17:02:50 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

	pthread_mutex_lock(&data->print);
	time = get_time_in_ms();
	printf("%lu %d %s\n", time - philo->data->start_simulation, philo->id,
		message);
	pthread_mutex_unlock(&data->print);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		safe_printf(philo->data, philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_printf(philo->data, philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		safe_printf(philo->data, philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork);
		safe_printf(philo->data, philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	safe_printf(philo->data, philo, "is eating");
	pthread_mutex_lock(&philo->data->lastmeal);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->lastmeal);
	timesleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	safe_printf(philo->data, philo, "is sleeping");
	timesleep(philo->data->time_to_sleep, philo->data);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	safe_printf(philo->data, philo, "has taken a fork");
	timesleep(philo->data->time_to_die, philo->data);
	safe_printf(philo->data, philo, "died");
	pthread_mutex_unlock(&philo->left_fork);
}

void	thinking(t_philo *philo)
{
	long	think_time;

	think_time = philo->data->time_to_die - philo->data->time_to_sleep
		- philo->data->time_to_eat;
	safe_printf(philo->data, philo, "is thinking");
	timesleep(think_time, philo->data);
}

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
			safe_printf(data, philo, "died");
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philo == 1)
		return (one_philo(philo), arg);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (!philo->data->dead)
	{
		if (is_dead(philo->data) == 1)
			break ;
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
	return (NULL);
}

void	init_fork(t_data *data)
{
	int	i;

	i = 0;
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
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->lastmeal, NULL);
	pthread_mutex_init(&data->meal, NULL);
	data->dead = false;
	data->start_simulation = get_time_in_ms();
	init_fork(data);
	while (i < data->nbr_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_simulation;
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
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
		return (error_exit("Creation of the thread failed.", data), 0);
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
		return (1);
	if (!create_thread(data))
		return (free(data), 1);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
	free(data);
}
