/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:30:33 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/03/26 14:41:29 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

static int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*src1;
	const unsigned char	*src2;
	size_t				i;

	src1 = (const unsigned char *)s1;
	src2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}

void	print_status(t_philo *philo, char *str)
{
	size_t		time;
	const char	*color;

	color = WHITE;
	if (ft_memcmp(str, "is eating", ft_strlen(str)) == 0)
		color = YELLOW;
	else if (ft_memcmp(str, "is thinking", ft_strlen(str)) == 0)
		color = GREEN;
	else if (ft_memcmp(str, "is sleeping", ft_strlen(str)) == 0)
		color = CYAN;
	else if (ft_memcmp(str, "died", ft_strlen(str)) == 0)
		color = RED;
	else if (ft_memcmp(str, "has taken one fork", ft_strlen(str)) == 0)
		color = MAGENTA;
	else if (ft_memcmp(str, "has taken another fork", ft_strlen(str)) == 0)
		color = MAGENTA;
	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time; 
	if (!is_dead(philo))
		printf("%s%zu%s %d %s%s%s\n", BLUE, time, RESET, philo->id, color, str, RESET);
	pthread_mutex_unlock(philo->write_lock);
}
