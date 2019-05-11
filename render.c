/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:36:51 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/12 01:21:04 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "render.h"
#include "init_mlx.h"
#include "mlx.h"
#include "scene.h"
#include "ray.h"

static int	thread_inner_loop(t_th_param *th)
{
	int	y;
	int	update;

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
	return (update);
}

static int	thread_call_finish(t_mymlx *ml)
{
	int i;
	int	finish_frame;

	finish_frame = 1;
	i = -1;
	while (++i < 4)
	{
		if (ml->update || ml->ray_w == ml->ray_w_max)
		{
			pthread_mutex_lock(&ml->thread_param[i].mutex);
			if (ml->ray_w == ml->ray_w_max
					&& ml->thread_param[i].state != state_wait)
				return (thread_unlockn(ml, i) - 1);
		}
		else
		{
			if (pthread_mutex_trylock(&ml->thread_param[i].mutex) != 0)
				return (thread_unlockn(ml, i - 1) - 1);
		}
		if (ml->thread_param[i].state != state_wait)
			finish_frame = 0;
	}
	return (finish_frame);
}

static int	render_frame(t_mymlx *ml)
{
	int	finish;

	finish = 0;
	if (!ml->update && ml->ray_w > 1)
		ml->ray_w /= 2;
	else if (ml->ray_w == 1)
		finish = 1;
	mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);
	if (!finish)
		wake_up(ml);
	return (finish);
}

void		*ray_thread(void *param)
{
	t_th_param	*th;

	th = (t_th_param*)param;
	while (1)
	{
		pthread_mutex_lock(&th->mutex);
		if (th->state == state_update)
			th->state = state_draw;
		if (th->state == state_quit)
		{
			pthread_mutex_unlock(&th->mutex);
			pthread_exit(NULL);
		}
		if (!thread_inner_loop(th) && th->state != state_quit)
		{
			th->state = state_wait;
			pthread_mutex_lock(&th->mutex_cond);
			pthread_mutex_unlock(&th->mutex);
			pthread_cond_wait(&th->cond, &th->mutex_cond);
			pthread_mutex_unlock(&th->mutex_cond);
			th->state = (th->state == state_quit) ? state_quit : state_draw;
		}
		else
			pthread_mutex_unlock(&th->mutex);
	}
}

int			render(void *param)
{
	int			i;
	int			finish_frame;
	t_mymlx		*ml;
	static int	finish = 0;

	ml = (t_mymlx*)param;
	if (ml->ray_w == 1 && !ml->update && finish)
		return (0);
	else
	{
		if ((finish_frame = thread_call_finish(ml)) == -1)
			return (0);
		if (!finish_frame && (ml->ray_w > 1 || ml->update))
		{
			i = -1;
			while (++i < 4)
				ml->thread_param[i].state =
					ml->update ? state_update : state_draw;
			wake_up(ml);
		}
		ml->ray_w = (ml->update) ? ml->ray_w_max : ml->ray_w;
		finish = (finish_frame) ? render_frame(ml) : 0;
		ml->update = thread_unlockn(ml, 3);
	}
	return (0);
}
