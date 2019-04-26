/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:18:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 09:13:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"
#include "marching.h"

void	ray_scan(t_mymlx *ml)
{
	int		x, y;
	double	d;
	t_vec3	ray_o;
	t_vec3	ray_d;
	unsigned int color;
	unsigned int col;

	ray_o = ml->cam.pos;
	ray_d = ml->cam.dir;
	y = 0;
	while (y < ml->h)
	{
		x = 0;
		while (x < ml->w)
		{
			ray_d.x = ((double)x / ml->w) * 2.0 - 1.0 - ml->cam.dir.x;
			ray_d.y = ((double)y / ml->h) * 2.0 - 1.0 - ml->cam.dir.y;
			ray_d.z = ml->cam.dir.z;
			ray_d = vec_normalize(ray_d);
			d = marching(ray_o, ray_d);
			//printf("d = %lf {%lf, %lf, %lf}\n", d, ray_d.x, ray_d.y, ray_d.z);
			col = (255.0 * (d / 100.0));
			color = (unsigned int)(255.0*255.0*col + 255.0*col + col);
			if (d == DIST_MAX)
				color = 0;
			//color = d < DIST_MAX ? 0xaaaaaa : 0x0;
			putpixel(ml, x, y, color);
			x++;
		}
		y++;
	}
}
