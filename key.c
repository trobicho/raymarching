/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 01:41:03 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/27 21:30:23 by trobicho         ###   ########.fr       */
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
		cam_translate(&ml->cam, (t_vec3){0.0, 0.0, 0.02});
	else if (keycode == 125)
		cam_translate(&ml->cam, (t_vec3){0.0, 0.0, -0.02});
	else if (keycode == 123)
		cam_translate(&ml->cam, (t_vec3){-0.02, 0.0, 0.0});
	else if (keycode == 124)
		cam_translate(&ml->cam, (t_vec3){0.02, 0.0, 0.0});
	else if (keycode == 86)
		cam_rotate(&ml->cam, -3.14 / 90, ml->cam.up);
	else if (keycode == 88)
		cam_rotate(&ml->cam, 3.14 / 90, ml->cam.up);
	else if (keycode == 84)
		cam_rotate(&ml->cam, -3.14 / 90, ml->cam.right);
	else if (keycode == 91)
		cam_rotate(&ml->cam, 3.14 / 90, ml->cam.right);
	else if (keycode == 89)
		cam_rotate(&ml->cam, -3.14 / 90, ml->cam.dir);
	else if (keycode == 92)
		cam_rotate(&ml->cam, 3.14 / 90, ml->cam.dir);
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
	ml->ray_w = 32;
	return (1);
}
