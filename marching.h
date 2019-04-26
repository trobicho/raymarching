/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marching.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:07:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 08:45:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARCHING_H
# define MARCHING_H
#include "vector.h"

#define MAX_STEP	100
#define DIST_MIN	0.003
#define DIST_MAX	20.0

double	marching(t_vec3 ray_o, t_vec3 ray_d);
#endif
