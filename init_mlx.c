/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:48:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/12 18:13:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_mlx.h"
#include "mlx.h"
#include "string.h"
#include "scene_free.h"

void			free_mlx(t_mymlx *ml)
{
	mlx_destroy_image(ml->mlx_ptr, ml->img_ptr);
	mlx_destroy_window(ml->mlx_ptr, ml->win_ptr);
	scene_free(&ml->scene);
}

int				ft_init(t_mymlx *init)
{
	if (!init || !(init->mlx_ptr = mlx_init()))
		return (0);
	init->cam.dir = (t_vec3){1.0, 0.0, 0.0};
	init->cam.up = (t_vec3){0.0, 1.0, 0.0};
	init->cam.right = (t_vec3){0.0, 0.0, 1.0};
	init->cam.pos = (t_vec3){-3.0, 2.0, 0.0};
	init->normal_disp = 0;
	init->scene.l_obj = 0;
	init->scene.l_light = 0;
	init->ray_w_max = 16;
	return (1);
}

static int		ft_aspect_ratio(int w, int h)
{
	if (w < 100 || h < 100 || w > 2488 || h > 1400)
		return (0);
	if (w == h || ((double)w / h) == 16.0 / 9.0 \
			|| ((double)w / h) == 4.0 / 3.0 \
			|| ((double)w / h) == 1.78)
		return (1);
	return (0);
}

int				ft_create_window(t_mymlx *init, int w, int h, char *name)
{
	char		*str;

	if (!init || !init->mlx_ptr || init->win_ptr \
			|| !ft_aspect_ratio(w, h))
		return (0);
	str = name ? name : "RTv1";
	if (!(init->win_ptr = mlx_new_window(init->mlx_ptr, w, h, str)))
		return (0);
	if (!(init->img_ptr = mlx_new_image(init->mlx_ptr, w, h)))
		return (0);
	init->buf = mlx_get_data_addr(init->img_ptr, &init->bpp, \
			&init->sline, &init->endian);
	init->bpp /= 8;
	init->w = w;
	init->h = h;
	return (1);
}
