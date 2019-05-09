/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:04:04 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 18:22:28 by trobicho         ###   ########.fr       */
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

t_vec3	vec_reflect(t_vec3 d, t_vec3 n)
{
	return (vec_sub(d, (vec_scalar(n, 2.0 * vec_dot(d, n)))));
}
