/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:43:56 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/10 21:02:03 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long ft_atol(const char *str)
{
	int i;
	long res;

	i = 0;
	res = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		exit_error("Error: Philosopher did not accept negative numbers");
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!is_digit(str[i]))
			exit_error("Error: Philosopher only accepts numbers");
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

static bool check_input(char **argv)
{
	int i;
	long nb;

	i = 1;
	while (argv[i])
	{
		nb = ft_atol(argv[i]);
		if (nb > INT_MAX)
			exit_error("Error: Number greater than INT_MAX");
		i++;
	}
	return (true);
}

bool parse_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		exit_error("Error: Wrong number of arguments\n"
			Y"Usage: ./philo number_of_philosophers time_to_die time_to_eat"
			" time_to_sleep [number_of_times_each_philosopher_must_eat]"RST);
	}
	if (!check_input(argv))
		exit_error("Error: Arguments must be positive integers");
	return (true);
}