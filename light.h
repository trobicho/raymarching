/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:20:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/11 23:50:29 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "ray.h"
# include "scene.h"

typedef struct	s_light_inf
{
	double	d;
	t_vec3	d_l;
	double	d_l2;
	t_vec3	diffuse;
	t_vec3	spec;
	double	vd;
}				t_light_inf;

t_vec3			get_bg_color(t_ray_inf ray);
t_vec3			get_phong(t_light *light, t_ray_inf ray, t_vec3 d_l, t_vec3 n);
t_vec3			get_color(t_scene *scene, t_ray_inf ray, int rebound);
t_vec3			light_calc(t_scene *scene, t_ray_inf ray);
t_vec3			get_normal(t_ray_inf ray);
#endif
