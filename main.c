/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:17:11 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 03:43:27 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_resturant *resturant)
{
	int	i;

	i = 0;
	while (i < resturant->table.philos)
	{
		if (pthread_create(&resturant->philos[i].thread, NULL,
				philo_routine, &resturant->philos[i]) != 0)
		{
			set_stop(resturant, 1);
			while (i > 0)
				pthread_join(resturant->philos[--i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	join_threads(t_resturant *resturant)
{
	int	i;

	i = 0;
	while (i < resturant->table.philos)
	{
		pthread_join(resturant->philos[i].thread, NULL);
		i++;
	}
}

static void	sync_last_meal(t_resturant *resturant)
{
	int		i;
	long	now;

	now = get_ms();
	pthread_mutex_lock(&resturant->meal_mutex);
	i = 0;
	while (i < resturant->table.philos)
	{
		if (resturant->philos[i].meals_eaten == 0)
			resturant->philos[i].last_meal = now;
		i++;
	}
	pthread_mutex_unlock(&resturant->meal_mutex);
}

static int	run_simulation(t_resturant *resturant)
{
	if (!start_threads(resturant))
	{
		destroy_resturant(resturant);
		return (error_exit(ERR_THREADS));
	}
	sync_last_meal(resturant);
	if (pthread_create(&resturant->monitor_thread, NULL,
			monitor_routine, resturant) != 0)
	{
		set_stop(resturant, 1);
		join_threads(resturant);
		destroy_resturant(resturant);
		return (error_exit(ERR_MONITOR));
	}
	pthread_join(resturant->monitor_thread, NULL);
	join_threads(resturant);
	destroy_resturant(resturant);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_resturant	resturant;
	t_error		err;

	err = parse_table(&table, argc, argv);
	if (err != ERR_NONE)
		return (error_exit(err));
	if (!init_resturant(&resturant, &table))
		return (error_exit(ERR_INIT));
	return (run_simulation(&resturant));
}
