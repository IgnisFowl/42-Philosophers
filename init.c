/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2@c1r4p1.42sp.org.br <aarie-c2@c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:47:28 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/03/25 20:42:56 by aarie-c2@c1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, t_philo *philos)
{
	data->dead = 0;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	data->philos = philos;
}

void	init_forks(pthread_mutex_t *forks, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	init_args(t_philo *philos, char **argv)
{
	philos->nbr = ft_atol(argv[1]);
	philos->time_to_die = ft_atol(argv[2]);
	philos->time_to_eat = ft_atol(argv[3]);
	philos->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philos->nbr_of_eats = ft_atol(argv[5]);
	else
		philos->nbr_of_eats = -1;
}

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks, \
	char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		init_args(&philos[i], argv);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
		philos[i].dead = &data->dead;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].write_lock = &data->write_lock;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].nbr - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

int	init_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	controler;
	int			i;

	if (!data->philos)
		return (1);
	if (pthread_create(&controler, NULL, &monitor, data->philos) != 0)
		finish_threads("Failed creating monitor thread", data, forks);
	i = 0;
	while (i < data->philos[0].nbr)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, \
			&data->philos[i]) != 0)
			finish_threads("Failed creating routine thread", data, forks);
		i++;
	}
	if (pthread_join(controler, NULL) != 0)
		finish_threads("Failed joining threads", data, forks);
	i = 0;
	while (i < data->philos[0].nbr)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			finish_threads("Failed joining threads", data, forks);
		i++;
	}
	return (0);
}
