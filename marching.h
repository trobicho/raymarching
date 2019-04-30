/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marching.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:07:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/30 00:58:50 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARCHING_H
# define MARCHING_H
#include "scene.h"
#include "vector.h"

#define MAX_STEP	2000
#define DIST_MIN	0.001
#define DIST_MAX	30.0

double	marching(t_scene *scene, t_vec3 ray_o, t_vec3 ray_d);
#endif
