/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marching.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:07:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/29 02:54:44 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARCHING_H
# define MARCHING_H
#include "vector.h"

#define MAX_STEP	2000
#define DIST_MIN	0.0003
#define DIST_MAX	30.0

double	marching(t_vec3 ray_o, t_vec3 ray_d, t_vec3 *p, int *hit);
#endif
