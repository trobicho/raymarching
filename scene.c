/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:58:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 08:45:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

/*
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
*/

/*
double	scene_get_dist(t_vec3 v)
{
	double	r = 1.0;

	return (vec_norme(v) - r);
}
*/

double	scene_get_dist(t_vec3 v)
{
	int		i;
	t_vec3	z = v;
	double	dr = 1.0;
	double	r = 0.0;
	double	theta;
	double	phi;
	double	zr;

	z.z = v.y;
	z.y = v.z;
	i = 0;
	while (i < 50)
	{
		r = vec_norme(z);
		if (r > 5.0)
			break;
		theta = acos(z.z / r);
		phi = atan2(z.y, z.x);
		dr = pow(r, 7.0) * 8.0 * dr + 1.0;
		zr = pow(r, 8.0);
		theta *= 8.0;
		phi *= 8.0;
		z = (t_vec3){zr*sin(theta)*cos(phi), zr*sin(phi)*sin(theta), zr*cos(theta)};
		z.x += v.x;
		z.z += v.y;
		z.y += v.z;
		i++;
	}
	return (0.5 * log(r) * r / dr);
}
