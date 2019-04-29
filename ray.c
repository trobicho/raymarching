/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:18:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/29 03:53:29 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vector.h"
#include "mlx.h"
#include "pixel.h"
#include "marching.h"
#include "ray.h"
#include "light.h"

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
	t_vec3	ray_d;
	t_vec3	p;
	t_vec3	color;
	unsigned int col;
	int			hit;
	t_light	light;

	light.pos = (t_vec3){0.0, 5.0, 0.0};
	light.pos = ml->cam.pos;
	light.intensity = 1.0;
	ray_d = ml->cam.dir;
	y = 0;
	while (y < ml->h)
	{
		x = 0;
		while (x < ml->w)
		{
			ray_d = pixel_to_ray(ml, x, ml->h - y);
			d = marching(ml->cam.pos, ray_d, &p, &hit);
			if (hit == 0)
				color = (t_vec3){0.0, 0.5, 0.2};
			else
			{
				/*
				col = (255.0 * (d / MAX_STEP));
				color = (unsigned int)(256*256*col + 256*col + col);
				*/
				color = light_calc(light, p, ml->normal_disp);
			}
			putpixel_vec_w(ml, x, y, ml->ray_w, color);
			x+=ml->ray_w;
		}
		y+=ml->ray_w;
	}
}
