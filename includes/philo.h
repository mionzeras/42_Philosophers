/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:43:48 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/21 16:44:13 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <limits.h> //INT_MAX
# include <pthread.h> //pthread
# include <unistd.h> //sleep
# include <stdbool.h> //bool
# include <sys/time.h> //gettimeofday

# define RST "\033[0m"
# define R "\033[1;31m"
# define Y "\033[1;33m"
# define MAX_PHILOS 200

typedef struct s_philo
{
	int				id;
	int				qtd_meals;
	int				left_fork_id;
	int				right_fork_id;
	long			last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int		nbr_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
	int		death_full;
	long	start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

//checker.c
int		finished_meals(t_data *data);
int		check_death(t_data *data);
int 	check_meals(t_data *data);
void	monitor(t_data *data);

//init.c
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
int		init_data(t_data *data, char **argv);

//parsing.c
long	ft_atol(const char *str);
void	parse_input(int argc, char **argv);

//routine.c
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	*routine(void *arg);

//utils.c
void	message(t_philo *philo, char *str);
int		ft_usleep(long time);
long	get_time(void);
int		free_program(t_data *data);
void	exit_error(char *str);

#endif