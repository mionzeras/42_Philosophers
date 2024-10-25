/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:51:17 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/25 15:41:47 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	message(t_philo *philo, char *str, char color)
{
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->death_full == 0)
	{
		if (color == 'r')
			printf(R "%ld %d %s\n" RST, get_time() - philo->data->start_time,
				philo->id, str);
		else if (color == 'y')
			printf(Y "%ld %d %s\n" RST, get_time() - philo->data->start_time,
				philo->id, str);
		else if (color == 'g')
			printf(G "%ld %d %s\n" RST, get_time() - philo->data->start_time,
				philo->id, str);
		else
			printf("%ld %d %s\n", get_time() - philo->data->start_time,
				philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->write);
}

int	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	free_program(t_data *data)
{
	int	i;

	ft_usleep(1000);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->dead_lock);
	i = -1;
	while (++i < data->nbr_philos)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->philos);
	return (0);
}

void	exit_error(char *str)
{
	printf(R "%s\n"RST, str);
	exit(EXIT_FAILURE);
}
