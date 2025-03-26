/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:51:00 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/03/26 15:52:47 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	release_forks(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
	}
}

static void	eating(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->right_fork);
		print_status(philos, "has taken one fork");
		pthread_mutex_lock(philos->left_fork);
		print_status(philos, "has taken another fork");
	}
	else
	{
		pthread_mutex_lock(philos->left_fork);
		print_status(philos, "has taken one fork");
		pthread_mutex_lock(philos->right_fork);
		print_status(philos, "has taken another fork");
	}
	philos->eating = 1;
	print_status(philos, "is eating");
	pthread_mutex_lock(philos->meal_lock);
	philos->last_meal = get_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->meal_lock);
	ft_usleep(philos->time_to_eat);
	philos->eating = 0;
	release_forks(philos);
}

static void	sleeping(t_philo *philos)
{
	print_status(philos, "is sleeping");
	ft_usleep(philos->time_to_sleep);
}

static void thinking(t_philo *philos)
{
	print_status(philos, "is thinking");
	ft_usleep(1);
}

void	*routine(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	if (philos->id % 2 == 0)
		ft_usleep(100);
	if (philos->nbr == 1)
		lonely_eating(philos);
	while (!is_dead(philos))
	{
		if (philos->id % 2 == 0)
		{
			eating(philos);
			sleeping(philos);
			thinking(philos);
		}
		else
		{
			thinking(philos);
			sleeping(philos);
			eating(philos);
		}
	}
	return (ptr);
}
