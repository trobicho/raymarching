/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:02:24 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/11 17:25:18 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

double			vec_norme(t_vec3 v);
t_vec3			vec_normalize(t_vec3 v);
t_vec3			vec_rotate(double angle, t_vec3 v);
t_vec3			vec_add(t_vec3 d1, t_vec3 d2);
t_vec3			vec_sub(t_vec3 d1, t_vec3 d2);
double			vec_dot(t_vec3 d1, t_vec3 d2);
t_vec3			vec_mul(t_vec3 d1, t_vec3 d2);
t_vec3			vec_scalar(t_vec3 d, double s);
t_vec3			vec_reflect(t_vec3 d, t_vec3 n);
t_vec3			vec_init(double x, double y, double z);
#endif
