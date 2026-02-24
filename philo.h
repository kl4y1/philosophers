/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:23:48 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 03:43:27 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef enum e_error
{
	ERR_NONE,
	ERR_INVALID_ARGS,
	ERR_INVALID_PHILO,
	ERR_INVALID_TIME,
	ERR_INVALID_MUST_EAT,
	ERR_INIT,
	ERR_THREADS,
	ERR_MONITOR
}	t_error;

typedef struct s_table
{
	int		philos;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	int		must_eat;
}	t_table;

typedef struct s_philo	t_philo;

typedef struct s_resturant
{
	t_table			table;
	long			start_time;
	int				stop;
	int				full_count;
	pthread_t		monitor_thread;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_resturant;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				meals_eaten;
	int				full;
	t_resturant		*resturant;
}	t_philo;

long	get_ms(void);
t_error	parse_table(t_table *c, int argc, char **argv);
int		init_resturant(t_resturant *resturant, const t_table *table);
void	destroy_resturant(t_resturant *resturant);
int		sim_stopped(t_resturant *resturant);
void	set_stop(t_resturant *resturant, int value);
void	print_state(t_philo *philo, char *msg);
void	smart_sleep(t_resturant *resturant, long ms);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
int		error_exit(t_error error);

#endif
