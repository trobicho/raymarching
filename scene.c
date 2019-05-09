/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:58:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 23:21:57 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "scene.h"
#include "operator.h"
#include "quaternion.h"

#include "de.h"
#include "transform.h"

double		scene_get_dist(t_scene *scene, t_vec3 v, t_object **obj_min)
{
	double		d_min;
	double		d;
	t_list_obj	*list;

	d_min = op_transform(&scene->l_obj->obj, v);
	if (obj_min)
		*obj_min = &scene->l_obj->obj;
	list = scene->l_obj->next;
	while (list != NULL)
	{
		d = op_transform(&list->obj, v);
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

static void	l_obj_init_elem(t_list_obj *l, t_vec3 pos, t_sdf_f sdf)
{
	l->next = NULL;
	l->obj.pos = pos;
	l->obj.sdf = sdf;
	l->obj.color = (t_vec3){1.0, 1.0, 1.0};
	l->obj.normal = (t_vec3){0.0, 1.0, 0.0};
	l->obj.spec = 1.0;
	l->obj.ks = 0.0;
	l->obj.rotate = (t_quaternion){0.0, 0.0, 0.0, 1.0};
	l->obj.is_rot = 0;
	l->obj.b_sphere_r = 0.0;
	l->obj.mirror = 0.0;
	l->obj.csg = NULL;
	l->obj.scale = 1.0;
}

void		init_obj(t_object *obj, t_vec3 pos, t_sdf_f sdf)
{
	obj->pos = pos;
	obj->sdf = sdf;
	obj->color = (t_vec3){1.0, 1.0, 1.0};
	obj->normal = (t_vec3){0.0, 1.0, 0.0};
	obj->spec = 1.0;
	obj->ks = 0.0;
	obj->rotate = (t_quaternion){0.0, 0.0, 0.0, 1.0};
	obj->is_rot = 0;
	obj->b_sphere_r = 0.0;
	obj->mirror = 0.0;
	obj->csg = NULL;
	obj->scale = 1.0;
}

t_object	*scene_add_obj(t_scene *scene, t_vec3 pos, t_sdf_f sdf)
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
	if ((list->next = (t_list_obj*)malloc(sizeof(t_list_obj))) == NULL)
		return (NULL);
	l_obj_init_elem(list->next, pos, sdf);
	return (&list->next->obj);
}

t_light		*scene_add_light(t_scene *scene, t_vec3 pos, double intensity)
{
	t_list_light	*list;
	t_vec3			color;

	color = (t_vec3){1.0, 1.0, 1.0};
	if (scene->l_light == NULL)
	{
		scene->l_light = (t_list_light*)malloc(sizeof(t_list_light));
		if (scene->l_light == NULL)
			return (NULL);
		scene->l_light->next = NULL;
		scene->l_light->light = (t_light){pos, color, intensity};
		return (&scene->l_light->light);
	}
	list = scene->l_light;
	while (list->next != NULL)
		list = list->next;
	if ((list->next = (t_list_light*)malloc(sizeof(t_list_light))) == NULL)
		return (NULL);
	list->next->next = NULL;
	list->next->light = (t_light){pos, color, intensity};
	return (&list->next->light);
}
