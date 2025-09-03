/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:22:39 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/03 17:40:46 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->lastmeal);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->print);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->philo[i].left_fork);
		i++;
	}
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	safe_printf(philo->data, philo, "has taken a fork");
	timesleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(&philo->left_fork);
}
