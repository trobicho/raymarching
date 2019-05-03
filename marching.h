/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marching.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:07:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/03 05:01:46 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARCHING_H
# define MARCHING_H
#include "scene.h"
#include "vector.h"

#define MAX_STEP	500
#define DIST_MIN	0.0001
#define DIST_MAX	300.0

double	marching(t_scene *scene, t_vec3 ray_o, t_vec3 ray_d, t_object **obj_min);
#endif
