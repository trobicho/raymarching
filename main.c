/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:32 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/06 21:01:19 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "mlx.h"
#include "init_mlx.h"
#include "ray.h"
#include "scene.h"
#include "de.h"
#include "transform.h"
#include "operator.h"

/*
static void	init(t_mymlx *ml)
{
	t_object	*obj;

	mlx_hook(ml->win_ptr, 2, 0, &key_hook, (void*)ml);
	mlx_hook(ml->win_ptr, 17, 0, &closer, (void*)ml);
	mlx_loop_hook(ml->mlx_ptr, &ray_loop, (void*)ml);
	scene_add_light(&ml->scene, (t_vec3){0.0, 3.0, 0.0}, 100000);
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &torus_de);
	calc_transform(obj, 33.3, 33.3, -33.3);
	obj->radius = 1.5;
	obj->radius2 = 0.3;
	obj->spec = 1000;
	obj->ks = 1000;
	obj->mirror = 0.9;
	obj->b_sphere_r = obj->radius + obj->radius2;
	obj->color = (t_vec3){0.5, 1.0, 0.0};
	obj->transform.mov = (t_vec3){0.0, 4.0, 2.0};
	obj->is_mov = 1;
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &sphere_de);
	obj->radius = 0.5;
	obj->transform.mov = (t_vec3){0.0, 4.0, 2.0};
	obj->is_mov = 1;
	obj->color = (t_vec3){1.0, 0.0, 0.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &sierpinski_de);
	obj->mirror = 0.4;
	obj->b_sphere_r = 1.7;
	obj->color = (t_vec3){1.0, 1.0, 0.0};
	calc_transform(obj, 33.3, 33.3, -33.3);
	obj->transform.mov = (t_vec3){0.0, 1.0, 2.0};
	obj->is_mov = 1;
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &mandelbulb_de);
	calc_transform(obj, 90.0, 45.0, 0.0);
	obj->transform.mov = (t_vec3){-3.0, 3.0, 2.0};
	obj->b_sphere_r = 1.0;
	obj->is_mov = 1;
	obj->radius = 1.0;
	obj->radius2 = 0.3;
	obj->spec = 1;
	obj->ks = 10;
	obj->color = (t_vec3){1.0, 1.0, 1.0};

	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &plane_de);
	obj->color = (t_vec3){0.0, 1.0, 1.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &plane_de);
	obj->transform.mov = (t_vec3){0.0, 20.0, 0.0};
	obj->is_mov = 1;
	obj->color = (t_vec3){0.0, 0.0, 1.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &plane_de);
	obj->normal = (t_vec3){0.0, 0.0, 1.0};
	obj->transform.mov = (t_vec3){0.0, 0.0, 20.0};
	obj->is_mov = 1;
	obj->color = (t_vec3){1.0, 0.0, 0.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &plane_de);
	obj->normal = (t_vec3){0.0, 0.0, 1.0};
	obj->transform.mov = (t_vec3){0.0, 0.0, -10.0};
	obj->is_mov = 1;
	obj->color = (t_vec3){1.0, 1.0, 0.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &plane_de);
	obj->normal = (t_vec3){1.0, 0.0, 0.0};
	obj->color = (t_vec3){0.0, 1.0, 0.0};
	obj->transform.mov = (t_vec3){20.0, 0.0, 0.0};
	obj->is_mov = 1;
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &plane_de);
	obj->color = (t_vec3){1.0, 0.0, 1.0};
	obj->normal = (t_vec3){1.0, 0.0, 0.0};
	obj->transform.mov = (t_vec3){-20.0, 0.0, 0.0};
	obj->is_mov = 1;
}
*/

static void	init(t_mymlx *ml)
{
	t_object	*obj;

	mlx_hook(ml->win_ptr, 2, 0, &key_hook, (void*)ml);
	mlx_hook(ml->win_ptr, 17, 0, &closer, (void*)ml);
	mlx_loop_hook(ml->mlx_ptr, &ray_loop, (void*)ml);

	ml->scene.ambient = 0.01;
	scene_add_light(&ml->scene, (t_vec3){-5.0, 4.0, 0.0}, 50.0);
	scene_add_light(&ml->scene, (t_vec3){5.0, 4.0, 0.0}, 50.0);

	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 1.0, -4.0}, &sierpinski_de);
	obj->b_sphere_r = 1.7;
	calc_transform(obj, 33.3, 33.3, -33.3);
	obj->color = (t_vec3){1.0, 0.0, 0.0};
	obj->radius = 0.6;
	obj->len = 0.2;

	obj = scene_add_obj(&ml->scene, (t_vec3){-3.2, 2.0, 3.0}, &sphere_de);
	obj->radius = 1.0;
	obj->spec = 10;
	obj->ks = 10;
	obj->mirror = 0.5;
	obj->color = (t_vec3){1.0, 0.0, 0.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){3.2, 2.0, 3.0}, &sphere_de);
	obj->color = (t_vec3){1.0, 1.0, 0.0};
	obj->mirror = 0.5;
	obj->radius = 1.0;
	obj->spec = 100;
	obj->ks = 0.1;

	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 2.0, 3.0}, &csg_sub);
	obj->b_sphere_r = 1.28;
	obj->csg = malloc(sizeof(t_csg));
	obj->mirror = 0.8;
	init_obj(&obj->csg->o1, (t_vec3){0.0, 0.0, 0.0}, &sphere_de);
	obj->csg->o1.radius = 1.28;
	init_obj(&obj->csg->o2, (t_vec3){0.0, 0.0, 0.0}, &csg_union);
	obj->csg->o2.csg = malloc(sizeof(t_csg));

	init_obj(&obj->csg->o2.csg->o1, (t_vec3){0.0, 0.0, 0.0}, &torus_de);
	obj->csg->o2.csg->o1.radius = 1.0;
	obj->csg->o2.csg->o1.radius2 = 0.4;
	calc_transform(&obj->csg->o2.csg->o1, 33.3, 33.3, -33.3);

	init_obj(&obj->csg->o2.csg->o2, (t_vec3){0.0, 0.0, 0.0}, &torus_de);
	obj->csg->o2.csg->o2.radius = 1.0;
	obj->csg->o2.csg->o2.radius2 = 0.4;
	calc_transform(&obj->csg->o2.csg->o2, -33.3, -33.3, 33.3);

	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 0.0}, &plane_de);
	obj->color = (t_vec3){0.0, 1.0, 1.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 20.0, 0.0}, &plane_de);
	obj->color = (t_vec3){0.0, 0.0, 1.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, 20.0}, &plane_de);
	obj->normal = (t_vec3){0.0, 0.0, 1.0};
	obj->color = (t_vec3){1.0, 0.0, 0.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, 0.0, -10.0}, &plane_de);
	obj->normal = (t_vec3){0.0, 0.0, 1.0};
	obj->color = (t_vec3){1.0, 1.0, 0.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){20.0, 0.0, 0.0}, &plane_de);
	obj->normal = (t_vec3){1.0, 0.0, 0.0};
	obj->color = (t_vec3){0.0, 1.0, 0.0};
	obj = scene_add_obj(&ml->scene, (t_vec3){-20.0, 0.0, 0.0}, &plane_de);
	obj->color = (t_vec3){1.0, 0.0, 1.0};
	obj->normal = (t_vec3){1.0, 0.0, 0.0};
}

/*
static void	init(t_mymlx *ml)
{
	t_object	*obj;

	mlx_hook(ml->win_ptr, 2, 0, &key_hook, (void*)ml);
	mlx_hook(ml->win_ptr, 17, 0, &closer, (void*)ml);
	mlx_loop_hook(ml->mlx_ptr, &ray_loop, (void*)ml);

	ml->scene.ambient = 0.05;
	scene_add_light(&ml->scene, (t_vec3){-50.0, 120.0, -50.0}, 100000.0);
	
	obj = scene_add_obj(&ml->scene, (t_vec3){0.0, -1.0, 0.0}, &plane_de);
	obj->color = (t_vec3){0.02, 0.02, 0.02};
	obj->mirror = 0.1;
	
	obj = scene_add_obj(&ml->scene, (t_vec3){50, 10, 50}, &sphere_de);
	obj->color = (t_vec3){0.16, 0.447, 0.898};
	obj->radius = 10;
	obj->spec = 64;
	obj->ks = 0.1;
	obj->mirror = 0.4;
	
	obj = scene_add_obj(&ml->scene, (t_vec3){25, 30, 40}, &sphere_de);
	obj->color = (t_vec3){0.9, 0.215, 0.215};
	obj->radius = 10;
	obj->mirror = 0.2;
}
*/

int	main(int ac, char **av)
{
	t_mymlx	ml;

	if (init_mlx(&ml, 1000, 1000, "marching") == -1)
		return (-1);
	init(&ml);
	ml.ray_w = 16;
	ray_scan(&ml);
	mlx_put_image_to_window(ml.mlx_ptr, ml.win_ptr, ml.img_ptr, 0, 0);
	mlx_loop(ml.mlx_ptr);
	return (0);
}
