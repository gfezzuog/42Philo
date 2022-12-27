/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfezzuog <gfezzuog@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:55:18 by gfezzuog          #+#    #+#             */
/*   Updated: 2022/12/27 23:55:20 by gfezzuog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->num_philo);
	if (!data->tid)
		return (ft_error(TID_ERR, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (ft_error(FORK_ERR, data));
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (ft_error(PHILO_ERR, data));
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->num_philo -1];
	i = 1;
	while (i < data->num_philo)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eat_cont = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	init_data(t_data *data, char **argv, int argc)
{
	data->num_philo = (int) ft_atoi(argv[1]);
	data->death_time = (u_int64_t) ft_atoi(argv[2]);
	data->eat_time = (u_int64_t) ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t) ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = (int) ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	if (data->num_philo <= 0 || data->num_philo > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
		return (ft_error(ERR_IN_2, NULL));
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	init(t_data *data, char **argv, int argc)
{
	if (init_data(data, argv, argc))
		return (1);
	if (alloc(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philos(data);
	return (0);
}
