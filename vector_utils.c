/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:20:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 18:21:32 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
