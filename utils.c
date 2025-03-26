/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:50:42 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/03/26 14:32:57 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
	c == '\r' || c == '\f' || c == '\v');
}

int	ft_atol(const char *nptr)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > LONG_MAX)
			return (-1);
		i++;
	}
	return (result);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("get_time() error\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
