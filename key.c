/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 01:41:03 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 06:18:55 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "camera.h"
#include "init_mlx.h"

int			closer(void *param)
{
	(void *)param;
	//free_mlx(ml);
	exit(0);
	return (0);
}

static int	key_cam(t_mymlx *ml, int keycode)
{
	if (keycode == 126)
		cam_translate(&ml->cam, (t_vec3){0.0, 0.0, 0.1});
	else if (keycode == 125)
		cam_translate(&ml->cam, (t_vec3){0.0, 0.0, -0.1});
	else if (keycode == 123)
		cam_translate(&ml->cam, (t_vec3){-1.0, 0.0, 0.0});
	else if (keycode == 124)
		cam_translate(&ml->cam, (t_vec3){1.0, 0.0, 0.0});
	else if (keycode == 86)
		cam_rotate(&ml->cam, 1.0, (t_vec3){0.0, 1.0, 0.0});
	else if (keycode == 88)
		cam_rotate(&ml->cam, -1.0, (t_vec3){0.0, 1.0, 0.0});
	else if (keycode == 84)
		cam_rotate(&ml->cam, 1.0, (t_vec3){1.0, 0.0, 0.0});
	else if (keycode == 91)
		cam_rotate(&ml->cam, -1.0, (t_vec3){1.0, 0.0, 0.0});
	else
		return (0);
	return (1);
}

int			key_hook(int keycode, void *param)
{
	t_mymlx	*ml;

	ml = (t_mymlx*)param;
	if (keycode == 53)
	{
		closer(param);
		return (0);
	}
	else if (key_cam(ml, keycode) == 0)
		return (0);
	ray_scan(ml);
	mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);
	return (1);
}
