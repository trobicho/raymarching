/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:48:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 08:45:32 by trobicho         ###   ########.fr       */
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
	init->cam.pos = (t_vec3){0.0, 0.0, -1.8};
	return (0);
}
