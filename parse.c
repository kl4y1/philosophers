/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:16:57 by mnajem            #+#    #+#             */
/*   Updated: 2026/02/24 03:43:27 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	digit_check(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoi(char *s)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		n = n * 10 + (s[i] - '0');
		if (n > 2147483647)
			return (-1);
		i++;
	}
	return (n);
}

static t_error	parse_values(long *dst, char **argv, int count)
{
	int		n;
	int		i;
	t_error	err;

	i = 0;
	while (i < count)
	{
		err = ERR_INVALID_TIME;
		if (i == 0)
			err = ERR_INVALID_PHILO;
		if (i == 4)
			err = ERR_INVALID_MUST_EAT;
		if (!digit_check(argv[i + 1]))
			return (err);
		n = ft_atoi(argv[i + 1]);
		if (n < 0)
			return (err);
		dst[i] = n;
		i++;
	}
	return (ERR_NONE);
}

static t_error	apply_values(t_table *c, long *v, int argc)
{
	c->philos = (int)v[0];
	c->t_die = v[1];
	c->t_eat = v[2];
	c->t_sleep = v[3];
	c->must_eat = -1;
	if (c->philos <= 0)
		return (ERR_INVALID_PHILO);
	if (c->t_die <= 0 || c->t_eat <= 0 || c->t_sleep <= 0)
		return (ERR_INVALID_TIME);
	if (argc == 6)
	{
		c->must_eat = (int)v[4];
		if (c->must_eat <= 0)
			return (ERR_INVALID_MUST_EAT);
	}
	return (ERR_NONE);
}

t_error	parse_table(t_table *c, int argc, char **argv)
{
	long	values[5];
	t_error	err;

	if (argc != 5 && argc != 6)
		return (ERR_INVALID_ARGS);
	err = parse_values(values, argv, argc - 1);
	if (err != ERR_NONE)
		return (err);
	return (apply_values(c, values, argc));
}
