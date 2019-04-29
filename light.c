/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:23:41 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/29 04:25:08 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "marching.h"
#include "light.h"

t_vec3	light_calc(t_light light, t_vec3 p, int normal)
{
	t_vec3	n;
	t_vec3	d_l;
	double	intensity_pix;
	double	d;
	t_vec3	color;

	color = (t_vec3){1.0, 1.0, 1.0};
	d_l = vec_normalize(vec_sub(light.pos, p));
	n = get_normal(p);
	intensity_pix = light.intensity * vec_dot(d_l, n);
	if (normal)
		return (n);
	if (intensity_pix < 0)
		intensity_pix = 0.0;
	d = marching(vec_add(p , vec_scalar(n, DIST_MIN * 1.5)), d_l, &p, 0);
	if (d < vec_norme(vec_sub(light.pos, p)))
		intensity_pix = 0.0;
	return (vec_scalar(color, intensity_pix));
}

t_vec3	get_normal(t_vec3 p)
{
	double	d;
	double	epsi;
	t_vec3	n;
	t_vec3	r;

	epsi = 0.00001;
	d = scene_get_dist(p);
	n = (t_vec3){d - scene_get_dist((t_vec3){p.x - epsi, p.y, p.z})
		, d - scene_get_dist((t_vec3){p.x, p.y - epsi,  p.z})
		, d - scene_get_dist((t_vec3){p.x, p.y, p.z - epsi})};
	//printf("{%lf, %lf, %lf}\n", n.x, n.y, n.z);
	r = vec_normalize(n);
	return (r);
}
