/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:18:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/05 04:10:06 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "vector.h"
#include "mlx.h"
#include "pixel.h"
#include "marching.h"
#include "ray.h"
#include "light.h"

int				ray_loop(void *param)
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
	double	d_s;
	t_vec3	r;
	double	lx;
	double	ly;

	d_s = 1.0;
	lx = ((double)x / ml->w) - 0.5;
	ly = ((double)y / ml->h) - 0.5;
	r.x = ml->cam.right.x * lx + ml->cam.up.x * ly + ml->cam.dir.x * d_s;
	r.y = ml->cam.right.y * lx + ml->cam.up.y * ly + ml->cam.dir.y * d_s;
	r.z = ml->cam.right.z * lx + ml->cam.up.z * ly + ml->cam.dir.z * d_s;
	return (vec_normalize(r));
}

void			ray_scan(t_mymlx *ml)
{
	int				x;
	int				y;
	t_vec3			color;
	unsigned int	col;
	t_ray_inf		ray;

	ray.r_o = ml->cam.pos;
	y = 0;
	while (y < ml->h)
	{
		x = 0;
		while (x < ml->w)
		{
			ray.r_d = pixel_to_ray(ml, x, ml->h - y);
			color = get_color(&ml->scene, ray, 5);
			putpixel_vec_w(ml, x, y, ml->ray_w, color);
			x += ml->ray_w;
		}
		y += ml->ray_w;
	}
}
