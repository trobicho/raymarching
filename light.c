/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:23:41 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/01 12:48:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "marching.h"
#include "light.h"

t_vec3	light_calc(t_scene *scene, t_vec3 p, t_object *obj_hit, int normal)
{
	t_vec3	n;
	t_vec3	d_l;
	double	d_l2;
	double	intensity_pix;
	double	d;
	t_light	light;

	light = scene->l_light->light;
	d_l = vec_normalize(vec_sub(light.pos, p));
	d_l2 = vec_norme(d_l);
	d_l2 *= d_l2;
	n = get_normal(scene, p);
	intensity_pix = pow((light.intensity * vec_dot(d_l, n) / d_l2), 1 / 2.2) / 255.0;
	if (normal)
		return (n);
	if (intensity_pix < 0.0)
		intensity_pix = 0.0;
	else if (intensity_pix > 1.0)
		intensity_pix = 1.0;
	else
	{
		d = marching(scene, vec_add(p , vec_scalar(n, DIST_MIN * 1.5)), d_l, NULL);
		if (d < vec_norme(vec_sub(light.pos, p)))
			intensity_pix = 0.0;
	}
	return (vec_scalar(obj_hit->color, intensity_pix));
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
