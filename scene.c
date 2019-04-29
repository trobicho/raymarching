/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:58:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/29 02:24:52 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"
#include "scene.h"

double	scene_get_dist(t_vec3 v)
{
	double	sd = mandelbulb_de(v);
	double	pd = v.y + 2.0;
	return (sd > pd ? pd : sd);
}

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

double	sphere_de(t_vec3 v)
{
	double	r = 1.0;

	return (vec_norme(v) - r);
}

double	torus_de(t_vec3 v)
{
	t_vec3	q;
	t_vec3	t;
	t_vec3	vtmp;

	t = (t_vec3){2.0, 0.5, 0.0};
	vtmp = (t_vec3){v.x, 0.0, v.z};
	q = (t_vec3){vec_norme(vtmp) - t.x, v.y, 0.0}; 
	return (vec_norme(q) - t.y);
}

/*
double	scene_get_dist(t_vec3 v)
{
	int		i;
	t_vec3	z = v;
	double	dr = 1.0;
	double	r = 0.0;
	double	theta;
	double	s_theta;
	double	phi;
	double	zr;

	z.z = v.y;
	z.y = v.z;
	i = 0;
	while (i < 10)
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
		s_theta = sin(theta);
		z = (t_vec3){zr*s_theta*cos(phi), zr*sin(phi)*s_theta, zr*cos(theta)};
		z.x += v.x;
		z.z += v.y;
		z.y += v.z;
		i++;
	}
	return (0.5 * log(r) * r / dr);
}
*/

double	mandelbulb_de(t_vec3 v)
{
	int		i;
	t_vec3	w;
	t_vec3	z;
	t_vec3	z2;
	t_vec3	z4;
	double	k[4];
	double	dr = 1.0;
	double	r;

	w = v;
	r = w.x * w.x + w.y * w.y + w.z * w.z;
	i = 0;
	while (i < 15)
	{
		dr = 8.0 * sqrt(r * r * r * r * r * r * r) * dr + 1.0;
		z = w;
		z2 = (t_vec3){z.x * z.x, z.y * z.y, z.z * z.z};
		z4 = (t_vec3){z2.x * z2.x, z2.y * z2.y, z2.z * z2.z};
		k[2] = z2.x + z2.z;
		k[1] = 1.0 / sqrt(k[2] * k[2] * k[2] * k[2] * k[2] * k[2] * k[2]);
		k[0] = z4.x + z4.y + z4.z - 6.0 * z2.y * z2.z - 6.0 * z2.x * z2.y + 2.0 * z2.z * z2.x;
		k[3] = z2.x - z2.y + z2.z;
		w.x = v.x + 64.0 * z.x * z.y * z.z * (z2.x - z2.z) * k[3] * (z4.x - 6.0 * z2.x * z2.z + z4.z) * k[0] * k[1];
		w.y = v.y + -16.0 * z2.y * k[2] * k[3] * k[3] + k[0] * k[0]; 
		w.z = v.z + -8.0 * z.y * k[3] * (z4.x * z4.x - 28.0 * z4.x * z2.x * z2.z + 70.0 * z4.x * z4.z - 28.0 * z2.x * z2.z * z4.z + z4.z * z4.z) * k[0] * k[1];
		r = w.x * w.x + w.y * w.y + w.z * w.z;
		if (r > 256.0)
			break;
		i++;
	}
	return (0.25 * log(r) * sqrt(r) / dr);
}

double	sierpinski_de(t_vec3 v)
{
	double	r;
	int		n;
	double	scale = 2.0;
	double	offset = 2.0;

	n = 0;
	while (n < 14)
	{
		if (v.x + v.y < 0)
			v = (t_vec3){-v.y, -v.x, v.z};
		if (v.x + v.z < 0)
			v = (t_vec3){-v.z, v.y, -v.x};
		if (v.y + v.z < 0)
			v = (t_vec3){v.x, -v.z, -v.y};
		v = vec_scalar(v, scale);
		v.x -= offset * (scale - 1.0);
		v.y -= offset * (scale - 1.0);
		v.z -= offset * (scale - 1.0);
		n++;
	}
	return ((vec_norme(v)) * pow(scale, (double)(-n)));
}
