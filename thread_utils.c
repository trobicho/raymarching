/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:16:37 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/11 16:28:23 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "render.h"
#include "init_mlx.h"

int		render_close(t_mymlx *ml)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		pthread_mutex_lock(&ml->thread_param[i].mutex);
		ml->thread_param[i].state = state_quit;
		pthread_mutex_unlock(&ml->thread_param[i].mutex);
		pthread_mutex_lock(&ml->thread_param[i].mutex_cond);
		pthread_cond_signal(&ml->thread_param[i].cond);
		pthread_mutex_unlock(&ml->thread_param[i].mutex_cond);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(ml->thread_tab[i], NULL);
		i++;
	}
	return (0);
}

int		render_init(t_mymlx *ml)
{
	int	i;

	i = 0;
	ml->ray_w = ml->ray_w_max;
	while (i < 4)
	{
		pthread_mutex_init(&ml->thread_param[i].mutex_cond, NULL);
		pthread_cond_init(&ml->thread_param[i].cond, NULL);
		ml->thread_param[i].id = i;
		ml->thread_param[i].ml = ml;
		ml->thread_param[i].state = state_draw;
		pthread_mutex_init(&ml->thread_param[i].mutex, NULL);
		if (pthread_create(&ml->thread_tab[i], NULL, &ray_thread
					, &ml->thread_param[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	wake_up(t_mymlx *ml)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		pthread_mutex_lock(&ml->thread_param[i].mutex_cond);
		pthread_cond_signal(&ml->thread_param[i].cond);
		pthread_mutex_unlock(&ml->thread_param[i].mutex_cond);
		i++;
	}
}

int		thread_unlockn(t_mymlx *ml, int n)
{
	int i;

	i = 0;
	while (i <= n)
	{
		pthread_mutex_unlock(&ml->thread_param[i].mutex);
		i++;
	}
	return (0);
}
