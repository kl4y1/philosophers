/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 02:18:20 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 02:18:33 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate(t_resturant *resturant)
{
	if (resturant->table.must_eat <= 0)
		return (0);
	pthread_mutex_lock(&resturant->meal_mutex);
	if (resturant->full_count == resturant->table.philos)
	{
		pthread_mutex_unlock(&resturant->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&resturant->meal_mutex);
	return (0);
}

static int	get_dead_id(t_resturant *resturant)
{
	int		i;
	int		id;
	int		full;
	long	last_meal;
	long	now;

	now = get_ms();
	i = 0;
	while (i < resturant->table.philos)
	{
		pthread_mutex_lock(&resturant->meal_mutex);
		id = resturant->philos[i].id;
		full = resturant->philos[i].full;
		last_meal = resturant->philos[i].last_meal;
		pthread_mutex_unlock(&resturant->meal_mutex);
		if (resturant->table.must_eat > 0 && full)
		{
			i++;
			continue ;
		}
		if (now - last_meal > resturant->table.t_die)
			return (id);
		i++;
	}
	return (0);
}

static void	print_death(t_resturant *resturant, int id)
{
	long	time;

	pthread_mutex_lock(&resturant->print_mutex);
	pthread_mutex_lock(&resturant->stop_mutex);
	if (!resturant->stop)
	{
		resturant->stop = 1;
		time = get_ms() - resturant->start_time;
		printf("%ld %d died\n", time, id);
	}
	pthread_mutex_unlock(&resturant->stop_mutex);
	pthread_mutex_unlock(&resturant->print_mutex);
}

void	*monitor_routine(void *arg)
{
	t_resturant	*resturant;
	int			id;

	resturant = (t_resturant *)arg;
	while (!sim_stopped(resturant))
	{
		if (all_ate(resturant))
		{
			set_stop(resturant, 1);
			return (NULL);
		}
		id = get_dead_id(resturant);
		if (id != 0)
		{
			print_death(resturant, id);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
