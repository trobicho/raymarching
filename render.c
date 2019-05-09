/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:36:51 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 22:08:44 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "init_mlx.h"
#include "mlx.h"
#include "scene.h"
#include "ray.h"

#include <stdio.h> //a degager

static void	*ray_thread(void *param)
{
	int			update;
	int			y;
	t_th_param	*th;

	th = (t_th_param*) param;
	while (1)
	{
		pthread_mutex_lock(&th->mutex);
		if (th->id != 3)
			printf("%d Iam here\n", th->id);
		if (th->ml->ray_w == th->ml->ray_w_max)
			printf("first frame\n");
		else
			printf("begin frame: %d\n", th->ml->ray_w);
		if (th->state == state_update)
			th->state = state_draw;
		if (th->state == state_quit)
		{
			printf("quit %d\n", th->id);
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
			printf("thread: %d, finish frame %d\n", th->id, th->ml->ray_w);
			th->state = state_wait;
			printf("%d Iam waiting\n", th->id);
			pthread_mutex_lock(&th->mutex_cond);
			pthread_mutex_unlock(&th->mutex);
			pthread_cond_wait(&th->cond, &th->mutex_cond);
			pthread_mutex_unlock(&th->mutex_cond);
			if (th->state != state_quit)
				th->state = state_draw;
			else
				printf("choper\n");
			printf("%d Iam ready to redrawing\n", th->id);
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
		printf("try to preclose %d\n", i);
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
		printf("try to close %d\n", i);
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
		finish_frame = 1;
		finish = 0;
		i = -1;
		while (++i < 4)
		{
			if (ml->update || ml->ray_w == ml->ray_w_max)
			{
				pthread_mutex_lock(&ml->thread_param[i].mutex);
				if (ml->ray_w == ml->ray_w_max &&
					ml->thread_param[i].state != state_wait)
				{
					a = -1;
					while (++a <= i)
						pthread_mutex_unlock(&ml->thread_param[a].mutex);
					return (0);
				}
			}
			else
			{
				if (pthread_mutex_trylock(&ml->thread_param[i].mutex) != 0)
				{
					a = -1;
					while (++a < i)
						pthread_mutex_unlock(&ml->thread_param[a].mutex);
					return (0);
				}
			}
			if (ml->thread_param[i].state != state_wait)
			{
				printf("not finish %d, %d\n", i, ml->ray_w);
				finish_frame = 0;
			}
		}
		i = -1;
		if (!finish_frame && (ml->ray_w > 1 || ml->update))
		{
			while (++i < 4)
			{
				ml->thread_param[i].state = 
					ml->update ? state_update : state_draw;
				if(!finish_frame)
				{
					pthread_mutex_lock(&ml->thread_param[i].mutex_cond);
					pthread_cond_signal(&ml->thread_param[i].cond);
					pthread_mutex_unlock(&ml->thread_param[i].mutex_cond);
				}
			}
		}
		if (ml->update)
			ml->ray_w = ml->ray_w_max;
		if (finish_frame)
		{
			if (finish_frame)
				printf("finish Frame!!\n");
			if (!ml->update && ml->ray_w > 1)
			{
				ml->ray_w /= 2;
				printf("w / 2.0 = %d\n", ml->ray_w);
			}
			else if (ml->ray_w == 1)
				finish = 1;
			mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);
			if (!finish)
			{
				printf("aweking everyone, (%d) %d\n", ml->update, ml->ray_w);
				i = -1;
				while (++i < 4)
				{
					pthread_mutex_lock(&ml->thread_param[i].mutex_cond);
					pthread_cond_signal(&ml->thread_param[i].cond);
					pthread_mutex_unlock(&ml->thread_param[i].mutex_cond);
				}
			}
		}
		i = -1;
		while (++i < 4)
			pthread_mutex_unlock(&ml->thread_param[i].mutex);
		ml->update = 0;
	}
	return (0);
}
