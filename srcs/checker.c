/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:51:05 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/21 21:10:12 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nbr_philos)
	{
		if (get_time() - data->philos[i].last_meal > data->time_to_die 
				&& data->philos[i].eating == 0)
		{
			message(&data->philos[i], "died");
			pthread_mutex_lock(&data->dead_lock);
			data->death_full = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (-1);
		}
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
	if (full_philos == data->nbr_philos)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->death_full = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (-1);
	}
	return (0);
}

void monitor(t_data *data)
{

    while (!loop_checker(data))
    {
		if (check_death(data) == 1)
			return ;
		ft_usleep(9);
		if (data->max_meals != -1)
			check_meals(data);
	}
}
