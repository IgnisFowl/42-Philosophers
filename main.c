/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:03:03 by aarie-c2@c1       #+#    #+#             */
/*   Updated: 2025/03/26 14:44:11 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(char **argv)
{
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > MAX_PHILOS \
	|| !is_digit(argv[1]))
		return (printf("Error: Wrong number of philosophers\n"), 1);
	if (ft_atol(argv[2]) < 1 || !is_digit(argv[2]))
		return (printf("Error: Wrong time to die\n"), 1);
	if (ft_atol(argv[3]) < 1 || !is_digit(argv[3]))
		return (printf("Error: Wrong time to eat\n"), 1);
	if (ft_atol(argv[4]) < 1 || !is_digit(argv[4]))
		return (printf("Error: Wrong time to sleep\n"), 1);
	if (argv[5] && (ft_atol(argv[5]) < 0 || !is_digit(argv[5])))
		return (printf("Error: Wrong time each philo must eat\n"), 1);
	return (0);
}

void	finish_threads(char *str, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str != NULL)
		printf("%s\n", str);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos[0].nbr)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	lonely_eating(t_philo *philos)
{
	pthread_mutex_lock(philos->right_fork);
	print_status(philos, "has taken one fork");
	ft_usleep(philos->time_to_die);
	pthread_mutex_unlock(philos->right_fork);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];

	if (argc != 5 && argc != 6)
		return (printf("Usage: ./philo [number of philosophers] \
			[time_to_die] [time_to_eat] [time_to_sleep] \
			[number_of_times_each_philosopher_must_eat]\n"), 1);
	if (parse_args(argv) == 1)
		return (1);
	init_data(&data, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, &data, forks, argv);
	init_threads(&data, forks);
	finish_threads(NULL, &data, forks);
	return (0);
}
