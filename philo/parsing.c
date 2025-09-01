/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:14:34 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/01 19:42:59 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atol(const char *nptr)
{
	int		sign;
	long	result;
	int		i;

	sign = 1;
	i = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i + 1] < '0' || nptr[i + 1] > '9')
			return (-1);
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c == '-' || c == '+')
		return (1);
	else
		return (0);
}

int	check_args(char *av)
{
	int		i;
	long	nbr;

	i = 0;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (error_exit("Only digits allowed."), 0);
		i++;
	}
	nbr = ft_atol(av);
	if (nbr < 0)
		return (error_exit("Only positive numbers allowed."), 0);
	else if (nbr > INT_MAX)
		return (error_exit("Numbers higher than INT_MAX are not allowed."), 0);
	return (1);
}

int	parsing2(char **av, t_data *data)
{
	if (check_args(av[2]))
		data->time_to_die = ft_atol(av[2]);
	else
		return (0);
	if (check_args(av[3]))
		data->time_to_eat = ft_atol(av[3]);
	else
		return (0);
	if (check_args(av[4]))
		data->time_to_sleep = ft_atol(av[4]);
	else
		return (0);
	return (1);
}

int	parsing(char **av, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	if (!av[1][0] || !av[2][0] || !av[3][0] ||!av[4][0])
		return (0);
	if (check_args(av[1]))
		data->nbr_philo = ft_atol(av[1]);
	else
		return (0);
	if (!parsing2(av, data))
		return (0);
	if (av[5] && av[5][0] != '\0')
	{
		if (check_args(av[5]))
			data->must_eat = ft_atol(av[5]);
		else
			return (0);
	}
	else
		data->must_eat = -1;
	if (data->nbr_philo > 200)
		return (error_exit("200 Philosophers maximum."), 0);
	return (1);
}
