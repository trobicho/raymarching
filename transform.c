/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:12:51 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/10 21:04:04 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "scene.h"
#include "vector.h"
#include "de.h"
#include <math.h>

static t_vec3	apply_rot(t_object *obj, t_vec3 p)
{
	t_quaternion	p_t;
	t_quaternion	q;

	q = obj->rotate;
	if (obj->is_rot)
	{
		p_t = (t_quaternion){p.x, p.y, p.z, 0.0};
		p_t = quat_mul(quat_mul(q, p_t), quat_conjug(q));
		p = (t_vec3){p_t.x, p_t.y, p_t.z};
	}
	return (p);
}

double			op_transform(t_object *obj, t_vec3 p)
{
	t_object	b_sphere;
	double		r;
	double		d;

	b_sphere.radius = obj->b_sphere_r;
	b_sphere.sdf = &sphere_de;
	b_sphere.scale = obj->scale;
	p = (t_vec3){p.x - obj->pos.x, p.y - obj->pos.y, p.z - obj->pos.z};
	if (obj->b_sphere_r > 0.0 && (r = op_scale(&b_sphere, p)) > 0.1)
		return (r);
	p = apply_rot(obj, p);
	d = op_scale(obj, p);
	return (d);
}

double			op_scale(t_object *obj, t_vec3 p)
{
	if (obj->scale != 1.0 && obj->scale >= 0.0)
		return (op_twist(obj, vec_scalar(p, 1.0 / obj->scale)) * obj->scale);
	return (op_twist(obj, p));
}

void			calc_transform(t_object *obj, double ax, double ay, double az)
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
