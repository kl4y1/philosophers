/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:17:32 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 02:05:05 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*error_msg(t_error error)
{
	if (error == ERR_INVALID_ARGS)
		return ("Error: invalid arguments");
	if (error == ERR_INVALID_PHILO)
		return ("Error: invalid number of philo");
	if (error == ERR_INVALID_TIME)
		return ("Error: invalid time value");
	if (error == ERR_INVALID_MUST_EAT)
		return ("Error: invalid must_eat value");
	if (error == ERR_INIT)
		return ("Error: init failed");
	if (error == ERR_THREADS)
		return ("Error: thread creation failed");
	if (error == ERR_MONITOR)
		return ("Error: monitor creation failed");
	return ("Error");
}

long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	destroy_resturant(t_resturant *resturant)
{
	int	i;

	i = 0;
	while (i < resturant->table.philos)
	{
		pthread_mutex_destroy(&resturant->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&resturant->meal_mutex);
	pthread_mutex_destroy(&resturant->print_mutex);
	pthread_mutex_destroy(&resturant->stop_mutex);
	pthread_cond_destroy(&resturant->start_cond);
	pthread_mutex_destroy(&resturant->start_mutex);
	free(resturant->forks);
	free(resturant->philos);
}

int	error_exit(t_error error)
{
	printf("%s\n", error_msg(error));
	return (1);
}
