/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:19:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/08 19:00:39 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	csg_free(t_csg *csg)
{
	if (csg)
	{
		if (csg->o1.csg)
			csg_free(csg->o1.csg);
		if (csg->o2.csg)
			csg_free(csg->o2.csg);
		free(csg);
	}
}

static void	l_obj_free(t_list_obj *l_obj)
{
	if (l_obj)
	{
		if (l_obj->next)
			l_obj_free(l_obj->next);
		csg_free(l_obj->obj.csg);
		free(l_obj);
	}
}

static void	l_light_free(t_list_light *l_light)
{
	if (l_light)
	{
		if (l_light->next)
			l_light_free(l_light->next);
		free(l_light);
	}
}

void	scene_free(t_scene *scene)
{
	if (scene)
	{
		l_obj_free(scene->l_obj);
		l_light_free(scene->l_light);
	}
}
