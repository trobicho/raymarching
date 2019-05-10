/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:20:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/10 20:38:36 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "ray.h"
# include "scene.h"

t_vec3	get_color(t_scene *scene, t_ray_inf ray, int rebound);
t_vec3	light_calc(t_scene *scene, t_ray_inf ray);
t_vec3	get_normal(t_ray_inf ray);
#endif
