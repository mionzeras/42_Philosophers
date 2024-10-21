/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:54:28 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/21 20:45:55 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data	data;
	pthread_mutex_t forks[MAX_PHILOS];
	
	data.forks = forks;
	parse_input(argc, argv);
	if (init_data(&data, argv) == -1)
		exit_error("Error: Data");
	if (init_mutexes(&data) == -1)
		exit_error("Error: Mutexes");
	if (init_philos(&data) == -1)
		exit_error("Error: Philos");
	monitor(&data);
	free_program(&data);
	return (0);
}
