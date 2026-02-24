/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 02:17:31 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 03:40:05 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	cleanup_init(t_resturant *resturant, int destroy_mutexes)
{
	if (destroy_mutexes)
	{
		pthread_cond_destroy(&resturant->start_cond);
		pthread_mutex_destroy(&resturant->start_mutex);
		pthread_mutex_destroy(&resturant->meal_mutex);
		pthread_mutex_destroy(&resturant->print_mutex);
		pthread_mutex_destroy(&resturant->stop_mutex);
	}
	free(resturant->forks);
	free(resturant->philos);
	return (0);
}

static int	init_mutexes(t_resturant *resturant)
{
	if (pthread_mutex_init(&resturant->stop_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&resturant->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&resturant->stop_mutex);
		return (0);
	}
	if (pthread_mutex_init(&resturant->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&resturant->print_mutex);
		pthread_mutex_destroy(&resturant->stop_mutex);
		return (0);
	}
	if (pthread_mutex_init(&resturant->start_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&resturant->meal_mutex);
		pthread_mutex_destroy(&resturant->print_mutex);
		pthread_mutex_destroy(&resturant->stop_mutex);
		return (0);
	}
	if (pthread_cond_init(&resturant->start_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&resturant->start_mutex);
		pthread_mutex_destroy(&resturant->meal_mutex);
		pthread_mutex_destroy(&resturant->print_mutex);
		pthread_mutex_destroy(&resturant->stop_mutex);
		return (0);
	}
	return (1);
}

static int	init_forks(t_resturant *resturant)
{
	int	i;

	i = 0;
	while (i < resturant->table.philos)
	{
		if (pthread_mutex_init(&resturant->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&resturant->forks[--i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	init_philos(t_resturant *resturant)
{
	int	i;
	int	n;

	n = resturant->table.philos;
	i = 0;
	while (i < n)
	{
		resturant->philos[i].id = i + 1;
		resturant->philos[i].thread = 0;
		resturant->philos[i].left_fork = &resturant->forks[i];
		resturant->philos[i].right_fork = &resturant->forks[(i + 1) % n];
		resturant->philos[i].last_meal = resturant->start_time;
		resturant->philos[i].meals_eaten = 0;
		resturant->philos[i].full = 0;
		resturant->philos[i].resturant = resturant;
		i++;
	}
}

int	init_resturant(t_resturant *resturant, const t_table *table)
{
	memset(resturant, 0, sizeof(t_resturant));
	resturant->table = *table;
	resturant->forks = malloc(sizeof(pthread_mutex_t)
			* resturant->table.philos);
	resturant->philos = malloc(sizeof(t_philo) * resturant->table.philos);
	if (!resturant->forks || !resturant->philos)
		return (cleanup_init(resturant, 0));
	memset(resturant->philos, 0, sizeof(t_philo) * resturant->table.philos);
	if (!init_mutexes(resturant))
		return (cleanup_init(resturant, 0));
	if (!init_forks(resturant))
		return (cleanup_init(resturant, 1));
	init_philos(resturant);
	return (1);
}
