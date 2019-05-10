/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:49:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/10 14:19:52 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "scene.h"
#include "vector.h"
#include <math.h>

double	op_twist(t_object *obj, t_vec3 p)
{
	double	c;
	double	s;
	t_vec3	q;

	if (obj->twist_factor == 0.0)
		return (obj->sdf(obj, p));
	c = cos(obj->twist_factor * p.x);
	s = sin(obj->twist_factor * p.x);
	q.x = p.x;
	q.y = c * p.y + -s * p.z;
	q.z = s * p.y + c * p.z;
	return (obj->sdf(obj, q));
}
