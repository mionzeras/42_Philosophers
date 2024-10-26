/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:51:05 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/25 23:23:32 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	loop_checker(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->death_full == 1)
		return (pthread_mutex_unlock(&data->dead_lock), 1);
	return (pthread_mutex_unlock(&data->dead_lock), 0);
}

int	check_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->meal);
		if (get_time() - data->philos[i].last_meal > data->time_to_die)
		{
			message(&data->philos[i], "died", 114);
			pthread_mutex_lock(&data->dead_lock);
			data->death_full = 1;
			pthread_mutex_unlock(&data->dead_lock);
			pthread_mutex_unlock(&data->meal);
			return (-1);
		}
		pthread_mutex_unlock(&data->meal);
	}
	return (0);
}

int	check_meals(t_data *data)
{
	int	i;
	int	full_philos;

	i = -1;
	full_philos = 0;
	while (++i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->meal);
		if (data->philos[i].qtd_meals >= data->max_meals
			&& data->max_meals != -1)
			full_philos++;
		pthread_mutex_unlock(&data->meal);
	}
	if (full_philos == data->nbr_philos)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->death_full = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (-1);
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!loop_checker(data))
	{
		if (check_death(data) == 1)
			break ;
		if (data->max_meals != -1)
			check_meals(data);
	}
	return (arg);
}
