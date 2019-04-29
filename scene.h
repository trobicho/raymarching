/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:57:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/28 22:58:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
#include "vector.h"

double	scene_get_dist(t_vec3 v);
t_vec3	scene_get_normal(t_vec3 v);
double	sphere_de(t_vec3 v);
double	torus_de(t_vec3 v);
double	mandelbulb_de(t_vec3 v);
double	sierpinski_de(t_vec3 v);
#endif
