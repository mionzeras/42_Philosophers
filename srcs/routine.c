/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:28:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/16 15:22:35 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(philo->left_fork);
	message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	message(philo, "has taken a fork");
	message(philo, "is eating");
	philo->last_meal = get_time();
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->meal);
	philo->qtd_meals++;
	pthread_mutex_unlock(philo->meal);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(100);
	while (philo->full_dead == false)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (arg);
}