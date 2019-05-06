/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marching.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:07:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/06 21:50:15 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARCHING_H
# define MARCHING_H
#include "scene.h"
#include "vector.h"

#define MAX_STEP	200
#define DIST_MIN	0.001
#define DIST_MAX	200.0

double	marching(t_scene *scene, t_vec3 ray_o, t_vec3 ray_d, t_object **obj_min);
double	marching_enh(t_scene *scene, t_vec3 ray_o, t_vec3 ray_d, t_object **obj_min);
#endif
