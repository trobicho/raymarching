/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 02:04:03 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 18:59:03 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"
#include "quaternion.h"

double			quat_length(t_quaternion q)
{
	return (sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}

t_quaternion	quat_normalize(t_quaternion q)
{
	double	len;

	len = quat_length(q);
	q.x /= len;
	q.y /= len;
	q.z /= len;
	q.w /= len;
	return (q);
}

t_quaternion	quat_conjug(t_quaternion q)
{
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	return (q);
}

t_quaternion	quat_mul(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	qr;

	qr.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	qr.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	qr.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	qr.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return (qr);
}

t_quaternion	quat_rotate(t_quaternion q, double angle, t_vec3 v)
{
	t_quaternion	tmp;

	tmp.x = v.x * sin(angle / 2.0);
	tmp.y = v.y * sin(angle / 2.0);
	tmp.z = v.z * sin(angle / 2.0);
	tmp.w = cos(angle / 2.0);
	q = quat_mul(quat_mul(tmp, q), quat_conjug(tmp));
	return (q);
}
