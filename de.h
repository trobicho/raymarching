/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   de.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:14:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/12 19:10:30 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DE_H
# define DE_H

# include "scene.h"

typedef struct	s_mandel_inf
{
	t_vec3	w;
	t_vec3	z;
	t_vec3	z2;
	t_vec3	z4;
	double	k[4];
	double	r;
}				t_mandel_inf;

double			sphere_de(t_object *obj, t_vec3 p);
double			torus_de(t_object *obj, t_vec3 p);
double			capped_cone_de(t_object *obj, t_vec3 p);
double			cone_de(t_object *obj, t_vec3 p);
double			cylinder_de(t_object *obj, t_vec3 p);
double			capped_cylinder_de(t_object *obj, t_vec3 p);
double			plane_de(t_object *obj, t_vec3 p);
double			mandelbulb_de(t_object *obj, t_vec3 v);
double			sierpinski_de(t_object *obj, t_vec3 v);
#endif
