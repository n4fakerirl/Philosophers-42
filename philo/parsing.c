/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:14:34 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/26 17:01:22 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_args(char *av, t_data *data)
{
	int		i;
	long	nbr;

	i = 0;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (error_exit("Only digits allowed.", data), 0);
		i++;
	}
	nbr = ft_atol(av);
	if (nbr < 0)
		return (error_exit("Only positive numbers allowed.", data), 0);
	else if (nbr > INT_MAX)
		return (error_exit("Numbers higher than INT_MAX are not allowed.",
				data), 0);
	return (1);
}

int	parsing(char **av, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	if (check_args(av[1], data))
		data->nbr_philo = ft_atol(av[1]);
	if (check_args(av[2], data))
		data->time_to_die = ft_atol(av[2]) * 1000;
	if (check_args(av[3], data))
		data->time_to_eat = ft_atol(av[3]) * 1000;
	if (check_args(av[4], data))
		data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5] && av[5][0] != '\0')
	{
		if (check_args(av[5], data))
			data->must_eat = ft_atol(av[5]);
	}
	else
		data->must_eat = -1;
	if (data->nbr_philo > 200)
		return (error_exit("200 Philosophers maximum.", data), 0);
	return (1);
}
