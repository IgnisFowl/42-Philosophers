/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:12:21 by aarie-c2          #+#    #+#             */
/*   Updated: 2025/03/26 14:37:17 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILOS 200

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define YELLOW  "\033[33m"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				nbr;
	int				nbr_of_eats;
	int				meals_eaten;
	int				*dead;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			last_meal;
	size_t			start_time;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	int				dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_data;

int			ft_atol(const char *nptr);
size_t		get_time(void);
int			is_digit(char *str);
int			is_dead(t_philo *philo);
void		print_status(t_philo *philo, char *str);
void		finish_threads(char *str, t_data *data, pthread_mutex_t *forks);
void		*monitor(void *ptr);
void		*routine(void *ptr);
void		init_data(t_data *data, t_philo *philos);
void		init_forks(pthread_mutex_t *forks, int nbr);
void		init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks, char **argv);
int			init_threads(t_data *data, pthread_mutex_t *forks);
int			ft_usleep(size_t milliseconds);
void		lonely_eating(t_philo *philos);


#endif