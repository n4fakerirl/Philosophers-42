/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:00:37 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/01 19:46:46 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	if (philo->data->must_eat != -1)
	{
		philo->nbr_meals++;
		if (philo->nbr_meals == philo->data->must_eat)
		{
			philo->full = true;
			philo->data->all_full++;
		}
	}
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
	pthread_mutex_unlock(&philo->left_fork);
}

void	thinking(t_philo *philo)
{
	long	ttk;

	ttk = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (ttk < 0)
		ttk = 0;
	safe_printf(philo->data, philo, "is thinking");
	if (ttk > 100)
		ttk -= 100;
	timesleep(ttk, philo->data);
}
