/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 02:00:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 06:35:46 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "quaternion.h"
#include <math.h>

void	cam_translate(t_cam *cam, t_vec3 v)
{
	cam->pos.x += v.x;
	cam->pos.y += v.y;
	cam->pos.z += v.z;
}

void	cam_rotate(t_cam *cam, double angle, t_vec3 v)
{
	t_quaternion	tmp;
	t_quaternion	view_tmp;

	tmp.x = v.x * sin(angle / 2.0);
	tmp.y = v.y * sin(angle / 2.0);
	tmp.z = v.z * sin(angle / 2.0);
	tmp.w = cos(angle / 2.0);
	view_tmp.x = cam->dir.x;
	view_tmp.y = cam->dir.y;
	view_tmp.z = cam->dir.z;
	view_tmp.w = 0.0;
	view_tmp = quat_mul(quat_mul(tmp, view_tmp), quat_conjug(tmp));
	printf("{%lf, %lf, %lf}, ", cam->dir.x, cam->dir.y, cam->dir.z);
	cam->dir = (t_vec3){view_tmp.x, view_tmp.y, view_tmp.z};
	printf("{%lf, %lf, %lf}\n", cam->dir.x, cam->dir.y, cam->dir.z);
}
