/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:58:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/03 01:15:08 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "scene.h"
#include "operator.h"

#include "de.h"
#include "transform.h"

double		scene_get_dist(t_scene *scene, t_vec3 v, t_object **obj_min)
{
	double		d_min;
	double		d;
	t_list_obj	*list;
	
	t_object	s_op = {.pos = (t_vec3){0.0,0.0,0.0}, .radius = 0.8, .radius2 = 0.2};

	//d_min = scene->l_obj->obj.sdf(&scene->l_obj->obj, v);
	d_min = op_transform(v, &scene->l_obj->obj);
	//d_min = op_intersect(torus_de(&s_op, v), scene->l_obj->obj.sdf(&scene->l_obj->obj, v));
	if (obj_min)
		*obj_min = &scene->l_obj->obj;
	list = scene->l_obj->next;
	while (list != NULL)
	{
		d = op_transform(v, &list->obj);
		if (d < d_min)
		{
			d_min = d;
			if (obj_min)
				*obj_min = &list->obj;
		}
		list = list->next;
	}
	return (d_min);
}

static void	l_obj_init_elem(t_list_obj *l, t_vec3 pos, sdf_f sdf)
{
	l->next = NULL;
	l->obj.pos = pos;
	l->obj.sdf = sdf;
	l->obj.color = (t_vec3){1.0, 1.0, 1.0};
	l->obj.spec = 1.0;
	l->obj.ks = 0.0;
	l->obj.transform = (t_transform){
		.q = (t_quaternion){0.0, 0.0, 0.0, 1.0},
		.mov = (t_vec3){0.0, 0.0, 0.0},
	};
	l->obj.is_rot = 0;
	l->obj.is_mov = 0;
}

t_object	*scene_add_obj(t_scene *scene, t_vec3 pos, sdf_f sdf)
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
		list = list->next;
	if ((list->next = (t_list_obj*)malloc(sizeof(t_list_obj))) == NULL) //free
		return (NULL);
	l_obj_init_elem(list->next, pos, sdf);
	return (&list->next->obj);
}

t_light		*scene_add_light(t_scene *scene, t_vec3 pos, double intensity)
{
	t_list_light	*list;

	if (scene->l_light == NULL)
	{
		scene->l_light = (t_list_light*)malloc(sizeof(t_list_light));
		if (scene->l_light == NULL)
			return (NULL);
		scene->l_light->next = NULL;
		scene->l_light->light = (t_light){pos, intensity};
		return (&scene->l_light->light);
	}
	list = scene->l_light;
	while (list->next != NULL)
		list = list->next;
	if ((list->next = (t_list_light*)malloc(sizeof(t_list_light))) == NULL) //free
		return (NULL);
	list->next->next = NULL;
	list->next->light = (t_light){pos, intensity};
	return (&list->next->light);
}
