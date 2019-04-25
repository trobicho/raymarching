/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:18:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/25 01:45:55 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"
#include "marching.h"

void	ray_scan(t_mymlx *ml, int w, int h)
{
	int		x, y;
	double	d;
	t_vec3	ray_o = (t_vec3){0.0, 0.0, -20.0};
	t_vec3	ray_d;
	unsigned int color;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			ray_d.x = ((double)x / w) * 2.0 - 1.0;
			ray_d.y = ((double)y / h) * 2.0 - 1.0;
			ray_d.z = 1.0;
			ray_d = vec_normalize(ray_d);
			d = marching(ray_o, ray_d);
			//printf("d = %lf {%lf, %lf, %lf}\n", d, ray_d.x, ray_d.y, ray_d.z);
			color = (unsigned int)(0xAAAAAA / (d/ 10.0));
			if (d == DIST_MAX)
				color = 0;
			//color = d < DIST_MAX ? 0xaaaaaa : 0x0;
			putpixel(ml, x, y, color);
			x++;
		}
		y++;
	}
}
