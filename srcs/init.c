/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:59:19 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/16 15:12:41 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_forks(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nbr_philos)
		pthread_mutex_init(&data->forks[i], NULL);
}

void init_philos(t_data *data, t_philo *philos)
{
	int		i;

	i = -1;
	while (++i < data->nbr_philos)
	{
		philos[i].id = i + 1;
		philos[i].qtd_meals = 0;
		philos[i].last_meal = data->start_time;
		philos[i].data = data;
		philos[i].full_dead = false;
		philos[i].eating = false;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->nbr_philos]; //dessa forma o garfo da direita do ultimo filosofo é o garfo do primeiro filosofo
		philos[i].write = &data->write;
		philos[i].meal = &data->meal;
		philos[i].dead = &data->dead;	
	}
}

void init_data(t_data *data, char **argv)
{
	data->nbr_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
	data->start_time = get_time();
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->meal, NULL);
}

void init_program(t_data *data, t_philo *philos, char **argv)
{
	init_data(data, argv);
	init_forks(data);
	init_philos(data, philos);
}
