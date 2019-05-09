/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:58:39 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 17:13:53 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scene.h"
#include "vector.h"

static double	tetrahedron(t_vec3 p)
{
	double	r;

	r = fmax(fmax(-p.x - p.y - p.z, p.x + p.y - p.z)
		, fmax(-p.x + p.y + p.z, p.x - p.y + p.z));
	r = (r - 1.0) / 1.73205080757;
	return (r);
}

double			sierpinski_de(t_object *obj, t_vec3 v)
{
	int		n;
	double	scale;
	double	offset;

	scale = 2.0;
	offset = 1.0;
	(void)obj;
	n = 0;
	while (n < 5)
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
	return (tetrahedron(v) * pow(scale, (double)(-n)));
}
