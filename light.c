/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:23:41 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/04 04:23:06 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "marching.h"
#include "light.h"

static double	get_phong(t_ray_inf ray, t_vec3 d_l, t_vec3 n)
{
	double	spec;
	double	phong_dot;

	phong_dot = vec_dot(vec_reflect(d_l, n), ray.r_d);
	if (phong_dot > 0.0)
		spec = pow(phong_dot, ray.obj_min->spec) * (ray.obj_min->spec + 2.0) / (2.0 * D_PI);
	else
		return (0.0);
	return (spec);
}

t_vec3	get_color(t_scene *scene, t_ray_inf ray, int rebound)
{
	if (rebound > 0)
	{
		ray.d = marching(scene, ray.r_o, ray.r_d, &ray.obj_min);
		if (ray.d >= DIST_MAX)
			return ((t_vec3){0.0, 0.5, 0.2});
		ray.p = vec_add(ray.r_o, vec_scalar(ray.r_d, ray.d));
		if (ray.obj_min->mirror > 0.0)
		{
			ray.r_o = vec_add(ray.r_o, vec_scalar(ray.r_d, ray.d));
			ray.r_d = vec_reflect(ray.r_d, get_normal(scene, ray.p));
			ray.r_o = vec_add(ray.r_o, vec_scalar(ray.r_d, DIST_MIN * 10.0));
			return (get_color(scene, ray, rebound - 1));
		}
	}
	else if(rebound <= 0)
		return ((t_vec3){0.0, 0.0, 0.0});
	return (light_calc(scene, ray, 0));
}

t_vec3	light_calc(t_scene *scene, t_ray_inf ray, int normal)
{
	t_vec3	n;
	t_vec3	d_l;
	t_vec3	color;
	double	d_l2;
	double	diffuse;
	double	intensity_pix;
	double	spec;
	double	d;
	t_light	light;

	light = scene->l_light->light;
	d_l = vec_normalize(vec_sub(light.pos, ray.p));
	d_l2 = vec_norme(d_l);
	d_l2 *= d_l2;
	n = get_normal(scene, ray.p);
	diffuse = pow((light.intensity * vec_dot(d_l, n) / d_l2), 1 / 2.2);
	spec = get_phong(ray, d_l, n) * ray.obj_min->ks;
	intensity_pix = diffuse / 255.0;
	if (normal)
		return (n);
	if (intensity_pix + spec < 0.0)
	{
		intensity_pix = 0.0;
		spec = 0.0;
	}
	else
	{
		d = marching(scene, vec_add(ray.p , vec_scalar(n, DIST_MIN * 10)), d_l, NULL);
		d += DIST_MIN * 10;
		if (d < vec_norme(vec_sub(light.pos, ray.p))) 
		{
			intensity_pix = 0.0;
			spec = 0.0; }
	}
	if (intensity_pix > 1.0)
		intensity_pix = 1.0;
	color = vec_scalar(ray.obj_min->color, intensity_pix);
	color.x += spec / 255.0;
	color.y += spec / 255.0;
	color.z += spec / 255.0;
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
