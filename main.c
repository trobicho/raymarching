/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:32 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/02 00:06:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "mlx.h"
#include "init_mlx.h"
#include "ray.h"
#include "scene.h"
#include "de.h"

static void	init(t_mymlx *ml)
{
	t_object	*obj;

	mlx_hook(ml->win_ptr, 2, 0, &key_hook, (void*)ml);
	mlx_hook(ml->win_ptr, 17, 0, &closer, (void*)ml);
	mlx_loop_hook(ml->mlx_ptr, &ray_loop, (void*)ml);
	scene_add_light(&ml->scene, (t_vec3){0.0, 3.0, -10.0}, 100000.0);
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &mandelbulb_de);
	obj->radius = 1.0;
	obj->radius2 = 0.3;
	obj->color = (t_vec3){1.0, 1.0, 1.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.4, -1.2}, &sphere_de);
	obj->radius = 0.1;
	obj->color = (t_vec3){0.7, 0.5, 0.3};
}

int	main(int ac, char **av)
{
	int	w = 1000;
	int h = 1000;
	t_mymlx	ml;

	if (init_mlx(&ml, w, h, "marching") == -1)
		return (-1);
	init(&ml);
	ml.ray_w = 32;
	ray_scan(&ml);
	mlx_put_image_to_window(ml.mlx_ptr, ml.win_ptr, ml.img_ptr, 0, 0);
	mlx_loop(ml.mlx_ptr);
	return (0);
}
