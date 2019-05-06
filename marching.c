/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:07:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/06 21:50:25 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "marching.h"
#include "scene.h"

double	marching(t_scene *scene, t_vec3 ray_o, t_vec3 ray_d, t_object **obj_min)
{
	int		i;
	double	d_o;
	double	d_s;
	t_vec3	p;

	i = 0;
	p = ray_o;
	d_o = 0.0;
	while (i < MAX_STEP)
	{
		p.x = ray_o.x + d_o * ray_d.x;
		p.y = ray_o.y + d_o * ray_d.y;
		p.z = ray_o.z + d_o * ray_d.z;
		d_s = scene_get_dist(scene, p, obj_min);
		d_o += d_s;
		if (d_o > DIST_MAX || d_s < DIST_MIN)
			break ;
		i++;
	}
	if (d_o > DIST_MAX)
		return (DIST_MAX);
	return (d_o);
}

double	marching_enh(t_scene *scene, t_vec3 ray_o, t_vec3 ray_d, t_object **obj_min)
{
	int		i;
	double	d_o;
	double	d_s;
	double	omega;
	double	prev_ds;
	double	step_len;
	int		sor_fail;
	t_vec3	p;

	omega = 1.6;
	i = 0;
	p = ray_o;
	d_o = 0.0;
	prev_ds = 0.0;
	sor_fail = 0;
	while (i < MAX_STEP)
	{
		p.x = ray_o.x + d_o * ray_d.x;
		p.y = ray_o.y + d_o * ray_d.y;
		p.z = ray_o.z + d_o * ray_d.z;
		d_s = scene_get_dist(scene, p, obj_min);
		sor_fail = omega > 1.0 && d_s + prev_ds < step_len;
		if (sor_fail)
		{
			step_len -= omega * step_len;
			omega = 1.0;
		}
		else
			step_len = d_s * omega;
		prev_ds = d_s;
		d_o += step_len;
		if (!sor_fail && (d_o > DIST_MAX || d_s < DIST_MIN))
			break ;
		i++;
	}
	if (d_o > DIST_MAX)
		return (DIST_MAX);
	return (d_o);
}
