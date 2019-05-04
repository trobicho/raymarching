/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:57:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/04 02:52:12 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# define D_PI	3.14159265
# include "quaternion.h"
# include "vector.h"

typedef struct	s_light
{
	t_vec3	pos;
	double	intensity;
}				t_light;

typedef struct	s_transform
{
	t_quaternion	q;
	t_vec3			mov;
}				t_transform;


typedef struct	s_object	t_object;

typedef double (*sdf_f)(struct s_object *object, t_vec3 p);

typedef struct	s_object
{
	t_vec3		pos;
	t_vec3		color;
	double		mirror;
	double		spec;
	double		radius;
	double		radius2;
	double		len;
	double		ks;
	sdf_f		sdf;
	t_transform	transform;
	int			is_rot;
	int			is_mov;
	double		b_sphere_r;
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
t_object		*scene_add_obj(t_scene *scene, t_vec3 pos, sdf_f sdf);
t_light			*scene_add_light(t_scene *scene, t_vec3 pos, double intensity);
#endif
