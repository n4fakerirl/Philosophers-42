/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:22:39 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/01 18:40:41 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
