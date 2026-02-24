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

void	wait_for_start(t_resturant *resturant)
{
	pthread_mutex_lock(&resturant->start_mutex);
	while (!resturant->start_ready)
		pthread_cond_wait(&resturant->start_cond, &resturant->start_mutex);
	pthread_mutex_unlock(&resturant->start_mutex);
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
	long	end;
	long	now;
	long	remaining;

	end = get_ms() + ms;
	while (!sim_stopped(resturant))
	{
		now = get_ms();
		if (now >= end)
			break ;
		remaining = end - now;
		if (remaining > 10)
			usleep(5000);
		else if (remaining > 2)
			usleep(1000);
		else
			usleep(200);
	}
}
