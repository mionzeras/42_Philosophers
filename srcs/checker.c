/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:51:05 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/16 15:23:46 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int check_death(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		message(philo, "died");
		pthread_mutex_lock(philo->dead);
		return (1);
	}
	return (0);
}

int check_meals(t_philo *philo)
{
	int i;
	int meals;
	
	i = -1;
	meals = 0;
	while (++i < philo->data->nbr_philos)
	{
		pthread_mutex_lock(philo->meal);
		if (philo[i].full_dead)
			meals++;
		pthread_mutex_unlock(philo->meal);
	}
	if (meals == philo->data->nbr_philos)
	{
		pthread_mutex_lock(philo->dead);
		philo->full_dead = true;
		pthread_mutex_unlock(philo->dead);
		return (1);
	}
	return (0);
}

void *checker(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo) || check_meals(philo))
			return (NULL);
	}
	return (NULL);
}*/

void *checker(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    int full_philos;

    while (1)
    {
        i = -1;
        full_philos = 0;
        while (++i < data->nbr_philos)
        {
            // Checar se o filósofo morreu
            pthread_mutex_lock(&data->meal);
            if (get_time() - data->philos[i].last_meal > data->time_to_die)
            {
                message(&data->philos[i], "died");
                pthread_mutex_lock(&data->dead);
                data->philos[i].full_dead = true;
                pthread_mutex_unlock(&data->dead);
                pthread_mutex_unlock(&data->meal);
                return (NULL);
            }
            pthread_mutex_unlock(&data->meal);

            // Checar se todos comeram o máximo de vezes
            if (data->max_meals != -1 && data->philos[i].qtd_meals >= data->max_meals)
                full_philos++;
        }
        if (full_philos == data->nbr_philos)
            return (NULL); // Todos comeram o máximo
        usleep(100); // Evitar sobrecarga da CPU
    }
    return (NULL);
}

