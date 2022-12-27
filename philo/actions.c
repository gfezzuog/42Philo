/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfezzuog <gfezzuog@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:55:13 by gfezzuog          #+#    #+#             */
/*   Updated: 2022/12/27 23:55:15 by gfezzuog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	message(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->l_fork);
	message(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	message(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	message(EATING, philo);
	philo->eat_cont++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
