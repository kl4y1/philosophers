/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 01:18:56 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 03:19:11 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_stopped(t_resturant *resturant)
{
	int	stop;

	pthread_mutex_lock(&resturant->stop_mutex);
	stop = resturant->stop;
	pthread_mutex_unlock(&resturant->stop_mutex);
	return (stop);
}

void	set_stop(t_resturant *resturant, int value)
{
	pthread_mutex_lock(&resturant->stop_mutex);
	resturant->stop = value;
	pthread_mutex_unlock(&resturant->stop_mutex);
}

void	print_state(t_philo *philo, char *msg)
{
	long	time;
	int		stop;

	pthread_mutex_lock(&philo->resturant->print_mutex);
	pthread_mutex_lock(&philo->resturant->stop_mutex);
	stop = philo->resturant->stop;
	pthread_mutex_unlock(&philo->resturant->stop_mutex);
	if (!stop)
	{
		time = get_ms() - philo->resturant->start_time;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->resturant->print_mutex);
}

void	smart_sleep(t_resturant *resturant, long ms)
{
	long	start;
	long	now;

	start = get_ms();
	while (!sim_stopped(resturant))
	{
		now = get_ms();
		if (now - start >= ms)
			break ;
		usleep(200);
	}
}
