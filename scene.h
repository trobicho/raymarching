/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:57:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 23:21:36 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "quaternion.h"
# include "vector.h"

typedef struct				s_light
{
	t_vec3	pos;
	t_vec3	color;
	double	intensity;
}							t_light;


typedef struct	s_object	t_object;

typedef double	(*t_sdf_f)(struct s_object *object, t_vec3 p);

typedef	struct	s_csg		t_csg;

struct						s_object
{
	t_vec3			pos;
	t_vec3			normal;
	t_vec3			color;
	double			mirror;
	double			spec;
	double			radius;
	double			radius2;
	double			len;
	double			ks;
	double			scale;
	t_sdf_f			sdf;
	t_quaternion	rotate;
	t_csg			*csg;
	int				is_rot;
	double			b_sphere_r;
};

struct						s_csg
{
	t_object	o1;
	t_object	o2;
};


typedef struct				s_list_obj
{
	t_object			obj;
	struct	s_list_obj	*next;
}							t_list_obj;

typedef struct				s_list_light
{
	t_light					light;
	struct	s_list_light	*next;
}							t_list_light;

typedef struct				s_scene
{
	t_list_light	*l_light;
	t_list_obj		*l_obj;
	double			ambient;
}							t_scene;

double						scene_get_dist(t_scene *scene, t_vec3 v
	, t_object **obj_min);
t_object					*scene_add_obj(t_scene *scene, t_vec3 pos
	, t_sdf_f sdf);
t_light						*scene_add_light(t_scene *scene, t_vec3 pos
	, double intensity);
void						init_obj(t_object *obj, t_vec3 pos
	, t_sdf_f sdf);
#endif
