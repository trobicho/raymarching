/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:18:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/28 01:18:10 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vector.h"
#include "mlx.h"
#include "pixel.h"
#include "marching.h"
#include "ray.h"

int		ray_loop(void *param)
{
	t_mymlx		*ml;
	static int	finish = 0;

	ml = (t_mymlx*)param;
	if (ml->ray_w == 1 && finish)
		return (0);
	else
	{
		finish = 0;
		ray_scan(ml);
		mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);
		if (ml->ray_w > 1)
			ml->ray_w /= 2;
		else
		{
			finish = 1;
		}
	}
	return (0);
}

static t_vec3	pixel_to_ray(t_mymlx *ml, int x, int y)
{
	double	d_s = 1.0;
	t_vec3	r;
	double	lx;
	double	ly;

	lx = ((double)x / ml->w) - 0.5;
	ly = ((double)y / ml->h) - 0.5;
	r.x = ml->cam.right.x * lx + ml->cam.up.x * ly + ml->cam.dir.x * d_s;
	r.y = ml->cam.right.y * lx + ml->cam.up.y * ly + ml->cam.dir.y * d_s;
	r.z = ml->cam.right.z * lx + ml->cam.up.z * ly + ml->cam.dir.z * d_s;
	return (r);
			
}

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
			ray_d = pixel_to_ray(ml, x, y);
			d = marching(ray_o, ray_d);
			col = (255.0 * (d / MAX_STEP));
			color = (unsigned int)(256*256*col + 256*col + col);
			if (d == DIST_MAX)
				color = 0x223399;
			//color = d < DIST_MAX ? 0xaaaaaa : 0x0;
			putpixel_w(ml, x, y, ml->ray_w, color);
			x+=ml->ray_w;
		}
		y+=ml->ray_w;
	}
}
