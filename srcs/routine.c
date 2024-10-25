/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:28:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/25 16:04:16 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo)
{
	message(philo, "is thinking", 0);
	ft_usleep(philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep);
}

void	sleeping(t_philo *philo)
{
	message(philo, "is sleeping", 0);
	ft_usleep(philo->data->time_to_sleep);
}

void	select_forks(t_philo *philo, int *first_fork, int *second_fork)
{
	*first_fork = philo->left_fork_id;
	*second_fork = philo->right_fork_id;
	if (philo->id == philo->data->nbr_philos || philo->id % 2 == 0)
	{
		*first_fork = philo->right_fork_id;
		*second_fork = philo->left_fork_id;
	}
}

void	eating(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	select_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	message(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	message(philo, "has taken a fork", 0);
	philo->eating = 1;
	message(philo, "is eating", 'g');
	pthread_mutex_lock(&philo->data->meal);
	philo->qtd_meals++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	message(philo, "is thinking", 0);
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!loop_checker(philo->data))
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
