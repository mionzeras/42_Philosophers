/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:51:05 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/21 16:43:02 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished_meals(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->death_full == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

int check_death(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nbr_philos && data->death_full == 0)
	{
		pthread_mutex_lock(&data->meal);
		if (get_time() - data->philos[i].last_meal > data->time_to_die)
		{
			message(&data->philos[i], "died");
			pthread_mutex_lock(&data->dead_lock);
			data->death_full = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->meal);
	}
	return (0);
}

int check_meals(t_data *data)
{
	int i;
	int full_philos;

	i = -1;
	full_philos = 0;
	while (++i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->meal);
		if (data->philos[i].qtd_meals >= data->max_meals && data->max_meals != -1)
			full_philos++;
		pthread_mutex_unlock(&data->meal);
	}
	return (full_philos);
}

void monitor(t_data *data)
{
    int i;

    while (data->death_full == 0)
    {
		if (check_death(data) == 1)
			return ;
		ft_usleep(9);
		if (data->max_meals != -1)
		{
			i = check_meals(data);
			if (i == data->nbr_philos)
			{
				pthread_mutex_lock(&data->dead_lock);
				data->death_full = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return ;
			}
    	}
	}
}
