/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:12:51 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/03 03:47:48 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "scene.h"

double	op_transform(t_vec3 p, t_object *obj)
{
	t_quaternion	p_t;
	t_transform		t;

	t = obj->transform;
	if (obj->is_mov)
		p = (t_vec3){p.x - t.mov.x, p.y - t.mov.y, p.z - t.mov.z};
	if (obj->is_rot)
	{
		p_t = (t_quaternion){p.x, p.y, p.z, 0.0};
		p_t = quat_mul(quat_mul(t.q, p_t), quat_conjug(t.q));
		p = (t_vec3){p_t.x, p_t.y, p_t.z};
	}
	return (obj->sdf(obj, p));
}

void	calc_transform(t_object *obj, double ax, double ay, double az)
{
	t_quaternion	qx;
	t_quaternion	qy;
	t_quaternion	qz;

	ax *= D_PI / 180.0;
	ay *= D_PI / 180.0;
	az *= D_PI / 180.0;

	qx.x = sin(-ax / 2.0);
	qx.y = 0.0;
	qx.z = 0.0;
	qx.w = cos(-ax / 2.0);

	qy.x = 0.0;
	qy.y = sin(-ay / 2.0);
	qy.z = 0.0;
	qy.w = cos(-ay / 2.0);
	
	qz.x = 0.0;
	qz.y = 0.0;
	qz.z = sin(-az / 2.0);
	qz.w = cos(-az / 2.0);

	obj->transform.q = quat_mul(quat_mul(qx, qy), qz);
	obj->is_rot = 1;
}
