/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:46:56 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 03:57:20 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
}

static void	eat_once(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->resturant->meal_mutex);
	philo->last_meal = get_ms();
	pthread_mutex_unlock(&philo->resturant->meal_mutex);
	print_state(philo, "is eating");
	smart_sleep(philo->resturant, philo->resturant->table.t_eat);
	pthread_mutex_lock(&philo->resturant->meal_mutex);
	philo->meals_eaten++;
	if (!philo->full && philo->resturant->table.must_eat > 0
		&& philo->meals_eaten >= philo->resturant->table.must_eat)
	{
		philo->full = 1;
		philo->resturant->full_count++;
	}
	pthread_mutex_unlock(&philo->resturant->meal_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	smart_sleep(philo->resturant, philo->resturant->table.t_die);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1 && philo->resturant->table.t_die
		> philo->resturant->table.t_eat + philo->resturant->table.t_sleep + 300)
		usleep(philo->resturant->table.t_eat * 500);
	if (philo->resturant->table.philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (!sim_stopped(philo->resturant))
	{
		if (philo->resturant->table.must_eat > 0 && philo->full)
			break ;
		eat_once(philo);
		print_state(philo, "is sleeping");
		smart_sleep(philo->resturant, philo->resturant->table.t_sleep);
		print_state(philo, "is thinking");
		if (philo->resturant->table.t_die > philo->resturant->table.t_eat
			+ philo->resturant->table.t_sleep + 300)
			usleep(2000);
	}
	return (NULL);
}
