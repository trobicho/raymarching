/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:58:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/30 14:59:03 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "scene.h"
#include "operator.h"

#include "de.h"

double		scene_get_dist(t_scene *scene, t_vec3 v)
{
	double		d_min;
	double		d;
	t_object	*obj_min;
	t_list_obj	*list;

	t_object	s_op = {.pos = (t_vec3){0.0,0.0,0.0}, .radius = 0.8, .radius2 = 0.2};

	//d_min = scene->l_obj->obj.sdf(&scene->l_obj->obj, v);
	d_min = op_intersect(torus_de(&s_op, v), scene->l_obj->obj.sdf(&scene->l_obj->obj, v));
	obj_min = &scene->l_obj->obj;
	list = scene->l_obj->next;
	while (list != NULL)
	{
		//d = list->obj.sdf(&list->obj, v);
		d = op_intersect(sphere_de(&s_op, v), list->obj.sdf(&list->obj, v));
		if (d < d_min)
		{
			d_min = d;
			obj_min = &list->obj;
		}
		list = list->next;
	}
	return (d_min);
}

static void	l_obj_init_elem(t_list_obj *l, t_vec3 pos
	, double (*sdf)(t_object *obj, t_vec3 v))
{
	l->next = NULL;
	l->obj.pos = pos;
	l->obj.sdf = sdf;
}

t_object	*scene_add_obj(t_scene *scene, t_vec3 pos
	, double (*sdf)(t_object *obj, t_vec3 v))
{
	t_list_obj	*list;

	if (scene->l_obj == NULL)
	{
		if ((scene->l_obj = (t_list_obj*)malloc(sizeof(t_list_obj))) == NULL)
			return (NULL);
		l_obj_init_elem(scene->l_obj, pos, sdf);
		return (&scene->l_obj->obj);
	}
	list = scene->l_obj;
	while (list->next != NULL)
	{
		list = list->next;
	}
	if ((list->next = (t_list_obj*)malloc(sizeof(t_list_obj))) == NULL) //free
		return (NULL);
	l_obj_init_elem(list->next, pos, sdf);
	return (&list->next->obj);
}
/*
double	scene_get_dist(t_vec3 v)
{
	double	sd = sierpinski_de(v);
	double	pd = v.y + 2.0;
	return (sd > pd ? pd : sd);
}
*/

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
