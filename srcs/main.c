/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:54:28 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/16 15:26:58 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int threads(t_data *data, t_philo *philos)
{
	int i;
	t_philo monitor	;

	i = -1;
 
	while (++i < data->nbr_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			free_program(data);
	}
	if (pthread_create(&monitor.thread, NULL, checker, &monitor))
		free_program(data);
	if (pthread_join(monitor.thread, NULL))
		free_program(data);
	i = -1;
	while (++i < data->nbr_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			free_program(data);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	philos[MAX_PHILOS];
	
	
	if (!parse_input(argc, argv))
		exit_error("Error: Invalid input");
	init_program(&data, philos, argv);
	if (threads(&data, philos))
		exit_error("Error: Threads");
	free_program(&data);
	return (0);
}