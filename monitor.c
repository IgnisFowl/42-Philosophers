/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:30:46 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/03/26 14:58:39 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eating(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].nbr_of_eats == -1)
		return (0);
	while (i < philos[0].nbr)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].nbr_of_eats)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].nbr)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

static int	philo_dead(t_philo *philos, size_t time_to_die)
{
	pthread_mutex_lock(philos->meal_lock);
	if (get_time() - philos->last_meal >= time_to_die && philos->eating == 0)
	{
		pthread_mutex_unlock(philos->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philos->meal_lock);
	return (0);
}

static int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nbr)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			print_status(&philos[i], "died");
			pthread_mutex_lock(philos[i].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
	{
		if (check_eating(philos) == 1 || check_death(philos) == 1)
			break ;
	}
	return (ptr);
}
