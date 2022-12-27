/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfezzuog <gfezzuog@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:55:30 by gfezzuog          #+#    #+#             */
/*   Updated: 2022/12/27 23:55:36 by gfezzuog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>

# define ERR_IN_2 "Invalid input values"

# define TID_ERR "Allocation Error: Thread ID"
# define FORK_ERR "Allocation Error: Forks"
# define PHILO_ERR "Allocation Error: Philos"

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define DIED "died"

# define TH_ERR "Error: Creating Threads"
# define JOIN_ERR "Error: Joining Threads"
# define INIT_ERR "Error: Init Forks"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	u_int64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				num_philo;
	int				num_meals;
	int				dead;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int			ft_error(char *str, t_data *data);
void		ft_exit(t_data *data);
void		clear_data(t_data *data);

int			init(t_data *data, char **argv, int argc);

long		ft_atoi(const char *str);
int			ft_usleep(useconds_t time);
int			ft_strcmp(char *s1, char *s2);
int			input_check(char **argv);

void		eat(t_philo *philo);
void		message(char *str, t_philo *philo);

u_int64_t	get_time(void);
int			thread_init(t_data *data);
void		*routine(void *philo_pointer);

#endif