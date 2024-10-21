/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:28:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/21 16:43:35 by gcampos-         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->forks[philo->left_fork_id]);
	message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork_id]);
	message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal);
	philo->qtd_meals++;
	message(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id]);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	message(philo, "is thinking");
	if (philo->id % 2 == 0) 
		ft_usleep(100);
	while (finished_meals(philo->data) == 0)
	{
		if (philo->data->nbr_philos == 1)
		{
			ft_usleep(philo->data->time_to_die);
			return (0);
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}
