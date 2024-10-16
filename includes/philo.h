/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:43:48 by gcampos-          #+#    #+#             */
/*   Updated: 2024/10/16 15:24:47 by gcampos-         ###   ########.fr       */
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
	long			last_meal;
	bool			full_dead;
	bool			eating;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*dead;	
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long	nbr_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals;
	long	start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;
	pthread_mutex_t	forks[MAX_PHILOS];
	struct s_philo	*philos;
}	t_data;

//checker.c
//int		check_death(t_philo *philo);
//int		check_meals(t_philo *philo);
void	*checker(void *arg);

//init.c
void	init_forks(t_data *data);
void	init_philos(t_data *data, t_philo *philos);
void	init_data(t_data *data, char **argv);
void	init_program(t_data *data, t_philo *philos, char **argv);

//main.c
int		threads(t_data *data, t_philo *philos);

//parsing.c
long	ft_atol(const char *str);
bool	parse_input(int argc, char **argv);

//routine.c
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	*routine(void *arg);

//utils.c
void	message(t_philo *philo, char *str);
int		ft_usleep(long time);
long	get_time(void);
void	free_program(t_data *data);
void	exit_error(char *str);

#endif