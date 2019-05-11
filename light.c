/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:23:41 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/11 23:52:32 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "marching.h"
#include "light.h"
#include "vector.h"

t_vec3	get_color(t_scene *scene, t_ray_inf ray, int rebound)
{
	t_vec3	color;
	t_vec3	color_reflect;

	color = vec_init(0.0, 0.0, 0.0);
	if (rebound > 0)
	{
		ray.d = marching(scene, ray.r_o, ray.r_d, &ray.obj_min);
		if (ray.d >= DIST_MAX)
			return (get_bg_color(ray));
		ray.p = vec_add(ray.r_o, vec_scalar(ray.r_d, ray.d));
		if (ray.obj_min->mirror < 1.0)
			color = light_calc(scene, ray);
		if (ray.obj_min->mirror > 0.0)
		{
			ray.r_o = vec_add(ray.r_o, vec_scalar(ray.r_d, ray.d));
			ray.r_d = vec_reflect(ray.r_d, get_normal(ray));
			ray.r_o = vec_add(ray.r_o, vec_scalar(ray.r_d, 10 * DIST_MIN));
			color_reflect = vec_scalar(get_color(scene, ray, rebound - 1)
					, ray.obj_min->mirror);
			color = vec_scalar(color, 1.0 - ray.obj_min->mirror);
			return (vec_add(color, color_reflect));
		}
		return (color);
	}
	return (vec_init(0.0, 0.0, 0.0));
}

t_vec3	light_one(t_scene *scene, t_ray_inf ray, t_light light)
{
	t_light_inf	l;
	t_vec3		n;
	t_vec3		v;

	l.d_l = vec_normalize(vec_sub(light.pos, ray.p));
	l.d_l2 = vec_norme(vec_sub(light.pos, ray.p));
	l.d_l2 *= l.d_l2;
	n = get_normal(ray);
	l.diffuse = vec_init(0.0, 0.0, 0.0);
	if ((l.vd = vec_dot(l.d_l, n)) > 0.0)
		l.diffuse = vec_scalar(vec_mul(light.color, ray.obj_min->color), l.vd);
	else
		return (vec_init(0.0, 0.0, 0.0));
	l.spec = vec_scalar(get_phong(&light, ray, l.d_l, n), ray.obj_min->ks);
	v = vec_add(ray.p, vec_scalar(n, 10 * DIST_MIN));
	l.d = marching(scene, v, l.d_l, NULL);
	l.d += 10 * DIST_MIN;
	if (l.d < vec_norme(vec_sub(light.pos, ray.p)))
	{
		l.diffuse = vec_init(0.0, 0.0, 0.0);
		l.spec = vec_init(0.0, 0.0, 0.0);
	}
	v = vec_add(l.diffuse, l.spec);
	return (vec_scalar(v, light.intensity / (M_PI * l.d_l2)));
}

t_vec3	light_calc(t_scene *scene, t_ray_inf ray)
{
	t_vec3			color;
	t_list_light	*l_light;

	l_light = scene->l_light;
	color = vec_scalar(ray.obj_min->color, scene->ambient);
	while (l_light)
	{
		color = vec_add(color, light_one(scene, ray, l_light->light));
		l_light = l_light->next;
	}
	color.x = pow(color.x, 1 / 2.2);
	color.y = pow(color.y, 1 / 2.2);
	color.z = pow(color.z, 1 / 2.2);
	return (color);
}
