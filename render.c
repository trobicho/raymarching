/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:36:51 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/10 23:11:01 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "init_mlx.h"
#include "mlx.h"
#include "scene.h"
#include "ray.h"

static void	*ray_thread(void *param)
{
	int			update;
	int			y;
	t_th_param	*th;

	th = (t_th_param*) param;
	while (1)
	{
		pthread_mutex_lock(&th->mutex);
		if (th->state == state_update)
			th->state = state_draw;
		if (th->state == state_quit)
		{
			pthread_mutex_unlock(&th->mutex);
			break ;
		}
		update = 0;
		y = th->id * th->ml->ray_w;
		while (y < th->ml->h)
		{
			if (th->ml->ray_w < th->ml->ray_w_max)
			{
				pthread_mutex_unlock(&th->mutex);
				pthread_mutex_lock(&th->mutex);
				if (th->state == state_update || th->state == state_quit)
				{
					update = 1;
					break ;
				}
			}
			ray_scan_hor(th->ml, y);
			y += th->ml->ray_w * 4;
		}
		if (!update && th->state != state_quit)
		{
			th->state = state_wait;
			pthread_mutex_lock(&th->mutex_cond);
			pthread_mutex_unlock(&th->mutex);
			pthread_cond_wait(&th->cond, &th->mutex_cond);
			pthread_mutex_unlock(&th->mutex_cond);
			if (th->state != state_quit)
				th->state = state_draw;
		}
		else
			pthread_mutex_unlock(&th->mutex);
	}
	pthread_exit(NULL);
}

int			render_close(t_mymlx *ml)
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

int			render_init(t_mymlx *ml)
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

static void	wake_up(t_mymlx *ml)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		pthread_mutex_lock(&ml->thread_param[i].mutex_cond);
		pthread_cond_signal(&ml->thread_param[i].cond);
		pthread_mutex_unlock(&ml->thread_param[i].mutex_cond);
		++i;
	}
}

void		thread_unlockn(t_mymlx *ml, int n)
{
	int i;

	i = 0;
	while (i <= n)
	{
		pthread_mutex_unlock(&ml->thread_param[i].mutex);
		i++;
	}
}

int			thread_call_finish(t_mymlx *ml)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (ml->update || ml->ray_w == ml->ray_w_max)
		{
			pthread_mutex_lock(&ml->thread_param[i].mutex);
			if (ml->ray_w == ml->ray_w_max &&
					ml->thread_param[i].state != state_wait)
			{
				thread_unlockn(ml, i);
				return (0);
			}
		}
		else
		{
			if (pthread_mutex_trylock(&ml->thread_param[i].mutex) != 0)
			{
				thread_unlockn(ml, i);
				return (0);
			}
		}
		if (ml->thread_param[i].state != state_wait)
			finish_frame = 0;
	}
}

int			render(void *param)
{
	int			a;
	int			i;
	int			finish_frame;
	t_mymlx		*ml;
	static int	finish = 0;

	ml = (t_mymlx*)param;
	if (ml->ray_w == 1 && !ml->update && finish)
		return (0);
	else
	{
		finish_frame = thread_call_finish(ml);
		finish = 0;
		i = -1;
		if (!finish_frame && (ml->ray_w > 1 || ml->update))
		{
			while (++i < 4)
				ml->thread_param[i].state = 
					ml->update ? state_update : state_draw;
			wake_up(ml);
		}
		if (ml->update)
			ml->ray_w = ml->ray_w_max;
		if (finish_frame)
		{
			if (!ml->update && ml->ray_w > 1)
				ml->ray_w /= 2;
			else if (ml->ray_w == 1)
				finish = 1;
			mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);
			if (!finish)
				wake_up(ml);
		}
		i = -1;
		while (++i < 4)
			pthread_mutex_unlock(&ml->thread_param[i].mutex);
		ml->update = 0;
	}
	return (0);
}
