/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 02:00:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/27 19:05:09 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "quaternion.h"
#include <math.h>

void	cam_translate(t_cam *cam, t_vec3 v)
{
	cam->pos.x += v.x * cam->right.x + v.y * cam->up.x + v.z * cam->dir.x;
	cam->pos.y += v.x * cam->right.y + v.y * cam->up.y + v.z * cam->dir.y;
	cam->pos.z += v.x * cam->right.z + v.y * cam->up.z + v.z * cam->dir.z;
}

void	cam_rotate(t_cam *cam, double angle, t_vec3 v)
{
	t_quaternion	view_tmp;

	view_tmp = (t_quaternion){cam->dir.x, cam->dir.y, cam->dir.z, 0.0};
	view_tmp = quat_rotate(view_tmp, angle, v);
	cam->dir = (t_vec3){view_tmp.x, view_tmp.y, view_tmp.z};
	view_tmp = (t_quaternion){cam->up.x, cam->up.y, cam->up.z, 0.0};
	view_tmp = quat_rotate(view_tmp, angle, v);
	cam->up = (t_vec3){view_tmp.x, view_tmp.y, view_tmp.z};
	view_tmp = (t_quaternion){cam->right.x, cam->right.y, cam->right.z, 0.0};
	view_tmp = quat_rotate(view_tmp, angle, v);
	cam->right = (t_vec3){view_tmp.x, view_tmp.y, view_tmp.z};
}
