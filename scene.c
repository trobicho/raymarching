/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:58:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/25 05:32:46 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	scene_get_dist(t_vec3 v)
{
	double	r = 1.0;

	v.x = fmod(v.x, 3.0);
	v.y = fmod(v.y, 3.0);
	v.z = fmod(v.z, 3.0) - 1.5;
	v.x += v.x < 0 ? 1.5 : -1.5; 
	v.y += v.y < 0 ? 1.5 : -1.5; 
	return (vec_norme(v) - r);
}

/*double scene_get_dist(t_vec3 v)
{
}*/
