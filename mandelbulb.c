/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbulb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:57:15 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 23:17:12 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scene.h"
#include "vector.h"
#include "de.h"

static void	calc_kw(t_mandel_inf *inf, t_vec3 v)
{
	inf->k[2] = inf->z2.x + inf->z2.z;
	inf->k[1] = 1.0
		/ sqrt(inf->k[2] * inf->k[2] * inf->k[2]
			* inf->k[2] * inf->k[2] * inf->k[2] * inf->k[2]);
	inf->k[0] = inf->z4.x + inf->z4.y + inf->z4.z - 6.0 * inf->z2.y * inf->z2.z
		- 6.0 * inf->z2.x * inf->z2.y + 2.0 * inf->z2.z * inf->z2.x;
	inf->k[3] = inf->z2.x - inf->z2.y + inf->z2.z;
	inf->w.x = v.x + 64.0 * inf->z.x * inf->z.y * inf->z.z
		* (inf->z2.x - inf->z2.z) * inf->k[3]
		* (inf->z4.x - 6.0 * inf->z2.x * inf->z2.z + inf->z4.z)
		* inf->k[0] * inf->k[1];
	inf->w.y = v.y + -16.0 * inf->z2.y * inf->k[2]
		* inf->k[3] * inf->k[3] + inf->k[0] * inf->k[0];
	inf->w.z = v.z + -8.0 * inf->z.y * inf->k[3]
		* (inf->z4.x * inf->z4.x - 28.0 * inf->z4.x * inf->z2.x
			* inf->z2.z + 70.0 * inf->z4.x * inf->z4.z - 28.0 * inf->z2.x
			* inf->z2.z * inf->z4.z + inf->z4.z * inf->z4.z)
		* inf->k[0] * inf->k[1];
}

double		mandelbulb_de(t_object *obj, t_vec3 v)
{
	int				i;
	t_mandel_inf	inf;
	double			dr;

	(void)obj;
	dr = 1.0;
	inf.w = v;
	inf.r = inf.w.x * inf.w.x + inf.w.y * inf.w.y + inf.w.z * inf.w.z;
	i = 0;
	while (i < 30)
	{
		dr = 8.0 * sqrt(inf.r * inf.r * inf.r * inf.r * inf.r * inf.r * inf.r)
			* dr + 1.0;
		inf.z = inf.w;
		inf.z2 = (t_vec3)
			{inf.z.x * inf.z.x, inf.z.y * inf.z.y, inf.z.z * inf.z.z};
		inf.z4 = (t_vec3)
			{inf.z2.x * inf.z2.x, inf.z2.y * inf.z2.y, inf.z2.z * inf.z2.z};
		calc_kw(&inf, v);
		inf.r = inf.w.x * inf.w.x + inf.w.y * inf.w.y + inf.w.z * inf.w.z;
		if (inf.r > 256.0)
			break ;
		i++;
	}
	return (0.25 * log(inf.r) * sqrt(inf.r) / dr);
}
