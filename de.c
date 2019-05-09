/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   de.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:15:24 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 19:18:43 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scene.h"
#include "vector.h"
#include "de.h"

double	sphere_de(t_object *obj, t_vec3 p)
{
	return (vec_norme(p) - obj->radius);
}

double	cylinder_de(t_object *obj, t_vec3 p)
{
	p.y = 0.0;
	return (vec_norme(p) - obj->radius);
}

double	plane_de(t_object *obj, t_vec3 p)
{
	if (obj->normal.x)
	{
		if (p.x < 0)
			return (-p.x - 0.1);
		return (p.x);
	}
	else if (obj->normal.y)
	{
		if (p.y < 0)
			return (-p.y - 0.1);
		return (p.y);
	}
	else if (obj->normal.z)
	{
		if (p.z < 0)
			return (-p.z - 0.1);
		return (p.z);
	}
	return (p.y);
}
