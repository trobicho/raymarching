/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 07:40:38 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/12 19:10:02 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H
# include "vector.h"

typedef struct	s_quaternion
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_quaternion;

double			quat_length(t_quaternion q);
t_quaternion	quat_normalize(t_quaternion q);
t_quaternion	quat_conjug(t_quaternion q);
t_quaternion	quat_mul(t_quaternion q1, t_quaternion q2);
t_quaternion	quat_rotate(t_quaternion q, double angle, t_vec3 v);
#endif
