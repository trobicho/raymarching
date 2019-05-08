/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:48:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/08 17:38:32 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_MLX
# define INIT_MLX

# include "camera.h"
# include "scene.h"
# include <pthread.h>

typedef enum	e_state
{
	state_quit, state_draw, state_finish_frame, state_update, state_wait
}				t_state;

typedef struct	s_mymlx t_mymlx; //tab?

typedef struct	s_th_param
{
	t_state			state;
	int				id;
	t_mymlx			*ml;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_mutex_t	mutex_cond;
}				t_th_param;


typedef struct	s_mymlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				w;
	int				h;
	int				ray_w;
	int				ray_w_max;
	char			*buf;
	int				bpp;
	int				sline;
	int				endian;
	t_cam			cam;
	t_scene			scene;
	int				normal_disp;
	t_th_param		thread_param[4];
	pthread_t		thread_tab[4];
	int				update;
}				t_mymlx;

int				init_mlx(t_mymlx *init, int w, int h, char *name);
void			free_mlx(t_mymlx *ml);
#endif
