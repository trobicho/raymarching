/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 23:48:25 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/13 14:29:06 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"
#include "ray.h"
#include "transform.h"
#include "tracing.h"

t_vec3	get_bg_color(t_ray_inf ray)
{
	double	t;
	t_vec3	blue;

	blue = (t_vec3){0.2, 0.4, 1.0};
	t = 0.5 * (ray.r_d.y + 1.0);
	return (vec_add(vec_init(1.0 - t, 1.0 - t, 1.0 - t), vec_scalar(blue, t)));
}

t_vec3	get_phong(t_light *light, t_ray_inf ray, t_vec3 d_l, t_vec3 n)
{
	double	spec;
	double	phong_dot;

	phong_dot = vec_dot(vec_reflect(d_l, n), ray.r_d);
	if (phong_dot > 0.0)
	{
		spec = pow(phong_dot, ray.obj_min->spec)
			* (ray.obj_min->spec + 2.0) / (2.0 * M_PI);
	}
	else
		return (vec_init(0.0, 0.0, 0.0));
	if (spec < 0.0)
		return (vec_init(0.0, 0.0, 0.0));
	return (vec_scalar(light->color, spec));
}

t_vec3	get_normal(t_ray_inf ray)
{
	double	d;
	double	epsi;
	t_vec3	n;
	t_vec3	p;

	p = ray.p;
	epsi = DIST_MIN / 2.0;
	d = op_transform(ray.obj_min, p);
	n.x = d - op_transform(ray.obj_min, vec_init(p.x - epsi, p.y, p.z));
	n.y = d - op_transform(ray.obj_min, vec_init(p.x, p.y - epsi, p.z));
	n.z = d - op_transform(ray.obj_min, vec_init(p.x, p.y, p.z - epsi));
	n = vec_normalize(n);
	return (n);
}
