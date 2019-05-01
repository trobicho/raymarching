/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:57:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/01 09:59:55 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
#include "vector.h"

typedef struct	s_light
{
	t_vec3	pos;
	double	intensity;
}				t_light;

typedef struct	s_object
{
	t_vec3	pos;
	t_vec3	color;
	double	radius;
	double	radius2;
	double	len;
	double	(*sdf)(struct s_object *object, t_vec3 p);
}				t_object;

typedef struct	s_list_obj
{
	t_object			obj;
	struct	s_list_obj	*next;
}				t_list_obj;

typedef struct	s_list_light
{
	t_light					light;
	struct	s_list_light	*next;
}				t_list_light;

typedef struct	s_scene
{
	t_list_light	*l_light;
	t_list_obj		*l_obj;
}				t_scene;

double			scene_get_dist(t_scene *scene, t_vec3 v, t_object **obj_min);
t_object		*scene_add_obj(t_scene *scene, t_vec3 pos
	, double (*sdf)(t_object *obj, t_vec3 v));
t_light			*scene_add_light(t_scene *scene, t_vec3 pos, double intensity);
#endif
