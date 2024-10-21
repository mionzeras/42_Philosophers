/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:28:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/21 21:06:57 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	loop_checker(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->death_full == 1)
		return (pthread_mutex_unlock(&data->dead_lock), 1);
	return (pthread_mutex_unlock(&data->dead_lock), 0);
}

void thinking(t_philo *philo)
{
	message(philo, "is thinking");
}

void sleeping(t_philo *philo)
{
	message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork_id]);
	message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork_id]);
	message(philo, "has taken a fork");
	philo->eating = 1;
	message(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal);
	philo->qtd_meals++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id]);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0) 
		ft_usleep(100);
	while (!loop_checker(philo->data))
	{
		if (philo->data->nbr_philos == 1)
		{
			ft_usleep(philo->data->time_to_die);
			return (0);
		}
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (0);
}
