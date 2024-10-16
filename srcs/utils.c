/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:51:17 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/16 14:29:52 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void message(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write);
	printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(philo->write);
}

int ft_usleep(long time)
{
	long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (0);
}

long get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void free_program(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nbr_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->dead);
}

void exit_error(char *str)
{
	printf(R "%s\n"RST, str);
	exit(EXIT_FAILURE);
}
