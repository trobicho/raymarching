/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:23:41 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/30 03:41:13 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "marching.h"
#include "light.h"

t_vec3	light_calc(t_scene *scene, t_vec3 p, int normal)
{
	t_vec3	n;
	t_vec3	d_l;
	double	intensity_pix;
	double	d;
	t_vec3	color;
	t_light	light;

	light = scene->light;
	color = (t_vec3){1.0, 1.0, 1.0};
	d_l = vec_normalize(vec_sub(light.pos, p));
	n = get_normal(scene, p);
	intensity_pix = pow(light.intensity * vec_dot(d_l, n), 1 / 2.2);
	if (normal)
		return (n);
	if (intensity_pix < 0)
		intensity_pix = 0.0;
	else
	{
		d = marching(scene, vec_add(p , vec_scalar(n, DIST_MIN * 1.5)), d_l);
		if (d < vec_norme(vec_sub(light.pos, p)))
			intensity_pix = 0.0;
	}
	return (vec_scalar(color, intensity_pix));
}

t_vec3	get_normal(t_scene *scene, t_vec3 p) //obj direct
{
	double	d;
	double	epsi;
	t_vec3	n;

	epsi = DIST_MIN / 2.0;
	d = scene_get_dist(scene, p);
	n = (t_vec3){d - scene_get_dist(scene, (t_vec3){p.x - epsi, p.y, p.z})
		, d - scene_get_dist(scene, (t_vec3){p.x, p.y - epsi,  p.z})
			, d - scene_get_dist(scene, (t_vec3){p.x, p.y, p.z - epsi})};
	//printf("{%lf, %lf, %lf}\n", n.x, n.y, n.z);
	n = vec_normalize(n);
	return (n);
}
