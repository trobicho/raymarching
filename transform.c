/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:12:51 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 23:22:31 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "scene.h"
#include "vector.h"
#include <math.h>

double	op_transform(t_object *obj, t_vec3 p)
{
	t_quaternion	p_t;
	t_quaternion	q;
	double			r;

	q = obj->rotate;
	p = (t_vec3){p.x - obj->pos.x, p.y - obj->pos.y, p.z - obj->pos.z};
	if (obj->b_sphere_r > 0.0 && (r = (vec_norme(p) - obj->b_sphere_r)) > 0.1)
		return (r);
	if (obj->is_rot)
	{
		p_t = (t_quaternion){p.x, p.y, p.z, 0.0};
		p_t = quat_mul(quat_mul(q, p_t), quat_conjug(q));
		p = (t_vec3){p_t.x, p_t.y, p_t.z};
	}
	if (obj->scale != 1.0 && obj->scale != 0.0)
		return (op_scale(obj, p));
	return (obj->sdf(obj, p));
}

double	op_scale(t_object *obj, t_vec3 p)
{
	return (obj->sdf(obj, vec_scalar(p, 1.0 / obj->scale)) * obj->scale);
}

void	calc_transform(t_object *obj, double ax, double ay, double az)
{
	t_quaternion	qx;
	t_quaternion	qy;
	t_quaternion	qz;

	ax *= M_PI / 180.0;
	ay *= M_PI / 180.0;
	az *= M_PI / 180.0;
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
	obj->rotate = quat_mul(quat_mul(qx, qy), qz);
	obj->is_rot = 1;
}
