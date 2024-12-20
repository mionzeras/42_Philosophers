/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:59:19 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/26 00:27:53 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_threads(t_data *data)
{
	int			i;
	t_philo		*philos;
	pthread_t	monitor;

	i = -1;
	philos = data->philos;
	while (++i < data->nbr_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
			return (free(data->forks), free(data->philos), -1);
	}
	if (pthread_create(&monitor, NULL, monitor_thread, data) != 0)
		return (-1);
	i = -1;
	while (++i < data->nbr_philos)
		pthread_join(philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}

int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	data->philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
		return (free(data->forks), -1);
	i = -1;
	philos = data->philos;
	data->start_time = get_time();
	while (++i < data->nbr_philos)
	{
		philos[i].id = i + 1;
		philos[i].qtd_meals = 0;
		philos[i].left_fork_id = i;
		philos[i].right_fork_id = (i + 1) % data->nbr_philos;
		philos[i].last_meal = data->start_time;
		philos[i].data = data;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (-1);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->meal, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (-1);
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->nbr_philos = ft_atol(argv[1]);
	if (data->nbr_philos > MAX_PHILOS)
		return (-1);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
	data->death_full = 0;
	return (0);
}
