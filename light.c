/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:23:41 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/05 06:03:33 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "marching.h"
#include "light.h"

static t_vec3	get_phong(t_light *light, t_ray_inf ray, t_vec3 d_l, t_vec3 n)
{
	double	spec;
	double	phong_dot;

	phong_dot = vec_dot(vec_reflect(d_l, n), ray.r_d);
	if (phong_dot > 0.0)
	{
		spec = pow(phong_dot, ray.obj_min->spec)
			* (ray.obj_min->spec + 2.0) / (2.0 * D_PI) / 255.0;
	}
	else
		return ((t_vec3){0.0, 0.0, 0.0});
	if (spec < 0.0)
		return ((t_vec3){0.0, 0.0, 0.0});
	return (vec_scalar(light->color, spec));
}

t_vec3	get_color(t_scene *scene, t_ray_inf ray, int rebound)
{
	t_vec3	color;
	t_vec3	color_reflect;
	
	t_vec3	color_tot;

	color = (t_vec3){0.0, 0.0, 0.0};
	if (rebound > 0)
	{
		ray.d = marching(scene, ray.r_o, ray.r_d, &ray.obj_min);
		if (ray.d >= DIST_MAX)
			return ((t_vec3){0.0, 0.5, 0.2});
		ray.p = vec_add(ray.r_o, vec_scalar(ray.r_d, ray.d));
		if (ray.obj_min->mirror < 1.0)
			color = light_calc(scene, ray, 0);
		if (ray.obj_min->mirror > 0.0)
		{
			ray.r_o = vec_add(ray.r_o, vec_scalar(ray.r_d, ray.d));
			ray.r_d = vec_reflect(ray.r_d, get_normal(scene, ray.p));
			ray.r_o = vec_add(ray.r_o, vec_scalar(ray.r_d, DIST_MIN * 10.0));
			color_reflect = vec_scalar(get_color(scene, ray, rebound - 1), ray.obj_min->mirror);
			color = vec_scalar(color, 1.0 - ray.obj_min->mirror);
			color_tot = (vec_add(color, color_reflect));
			return (vec_add(color, color_reflect));
		}
	}
	else
		return ((t_vec3){0.0, 0.0, 0.0});
	return (color);
}

t_vec3	light_calc(t_scene *scene, t_ray_inf ray, int normal)
{
	t_vec3	n;
	t_vec3	d_l;
	t_vec3	color;
	t_vec3	colorprev;
	double	d_l2;
	t_vec3	diffuse;
	t_vec3	spec;
	double	d;
	t_light	light;
	t_list_light	*l_light;
	double	vd;

	l_light = scene->l_light;
	color = vec_scalar(ray.obj_min->color, scene->ambient);
	while (l_light)
	{
		light = l_light->light;
		d_l = vec_normalize(vec_sub(light.pos, ray.p));
		d_l2 = vec_norme(d_l);
		d_l2 *= d_l2;
		n = get_normal(scene, ray.p);
		diffuse = (t_vec3){0.0, 0.0, 0.0};
		if ((vd = vec_dot(d_l, n)) > 0.0)
			diffuse = vec_scalar(vec_mul(light.color, ray.obj_min->color), 1 / 255.0);
		spec = vec_scalar(get_phong(&light, ray, d_l, n), ray.obj_min->ks);
		if (normal)
			return (n);
		else
		{
			d = marching(scene, vec_add(ray.p , vec_scalar(n, DIST_MIN * 10)), d_l, NULL);
			d += DIST_MIN * 10;
			if (d < vec_norme(vec_sub(light.pos, ray.p))) 
			{
				diffuse = (t_vec3){0.0, 0.0, 0.0};
				spec = (t_vec3){0.0, 0.0, 0.0};
			}
		}
		if (vd > 0.0)
			color = vec_add(color, vec_scalar(vec_add(diffuse, spec)
					, pow((light.intensity * vd / d_l2), 1 / 2.2)));
		l_light = l_light->next;
	}
	return (color);
}

t_vec3	get_normal(t_scene *scene, t_vec3 p) //obj direct
{
	double	d;
	double	epsi;
	t_vec3	n;

	epsi = DIST_MIN / 2.0;
	d = scene_get_dist(scene, p, NULL);
	n = (t_vec3){d - scene_get_dist(scene, (t_vec3){p.x - epsi, p.y, p.z}, NULL)
		, d - scene_get_dist(scene, (t_vec3){p.x, p.y - epsi,  p.z}, NULL)
			, d - scene_get_dist(scene, (t_vec3){p.x, p.y, p.z - epsi}, NULL)};
	n = vec_normalize(n);
	return (n);
}
