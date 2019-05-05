/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:04:04 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/05 01:10:47 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "quaternion.h"
#include <math.h>

double	vec_norme(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec_normalize(t_vec3 v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
}

t_vec3	vec_rotate(double angle, t_vec3 v)
{
	t_quaternion	view_tmp;

	view_tmp.x = v.x;
	view_tmp.y = v.y;
	view_tmp.z = v.z;
	view_tmp.w = 0.0;
	view_tmp = quat_rotate(view_tmp, angle, v);
	v = (t_vec3){view_tmp.x, view_tmp.y, view_tmp.z};
	return (v);
}

t_vec3	vec_sub(t_vec3 d1, t_vec3 d2)
{
	return (t_vec3){d1.x - d2.x, d1.y - d2.y, d1.z - d2.z};
}

t_vec3	vec_add(t_vec3 d1, t_vec3 d2)
{
	return (t_vec3){d1.x + d2.x, d1.y + d2.y, d1.z + d2.z};
}

double	vec_dot(t_vec3 d1, t_vec3 d2)
{
	return (d1.x * d2.x + d1.y * d2.y + d1.z * d2.z);
}

t_vec3	vec_mul(t_vec3 d1, t_vec3 d2)
{
	return (t_vec3){d1.x * d2.x, d1.y * d2.y, d1.z * d2.z};
}

t_vec3	vec_scalar(t_vec3 d, double s)
{
	return (t_vec3){d.x * s, d.y * s, d.z * s};
}

t_vec3	vec_reflect(t_vec3 d, t_vec3 n)
{
	return vec_sub(d, (vec_scalar(n, 2.0 * vec_dot(d, n))));
}
