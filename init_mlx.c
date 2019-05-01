/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:48:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/01 09:07:46 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_mlx.h"
#include "mlx.h"
#include "string.h"

int	init_mlx(t_mymlx *init, int w, int h, char *name)
{
	if ((init->mlx_ptr = mlx_init()) == NULL)
	{
		return (-1);
	}
	if (name)
		init->win_ptr = mlx_new_window(init->mlx_ptr, w, h, name);
	else
		init->win_ptr = mlx_new_window(init->mlx_ptr, w, h, "no_name");
	init->img_ptr = mlx_new_image(init->mlx_ptr, w, h);
	init->buf = mlx_get_data_addr(init->img_ptr, &init->bpp,
									&init->sline, &init->endian);
	init->bpp /= 8;
	init->w = w;
	init->h = h;
	init->cam.dir = (t_vec3){0.0, 0.0, 1.0};
	init->cam.up = (t_vec3){0.0, 1.0, 0.0};
	init->cam.right = (t_vec3){1.0, 0.0, 0.0};
	init->cam.pos = (t_vec3){0.0, 0.0, -3.0};
	init->normal_disp = 0;
	init->scene.l_obj = NULL;
	init->scene.l_light = NULL;
	return (0);
}
