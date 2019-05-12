/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:18:16 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/12 18:06:34 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scene.h"
#include "vector.h"
#include "de.h"

double	torus_de(t_object *obj, t_vec3 p)
{
	t_vec3	q;
	t_vec3	t;
	t_vec3	p_tmp;

	t = vec_init(obj->radius, obj->radius2, 0.0);
	p_tmp = vec_init(p.x, 0.0, p.z);
	q = vec_init(vec_norme(p_tmp) - t.x, p.y, 0.0);
	return (vec_norme(q) - t.y);
}

double	capped_cone_de(t_object *obj, t_vec3 p)
{
	double		angle;
	double		tmp;
	int			b;

	b = 0;
	if (obj->len <= 0 && (b = 1))
		obj->len = 1;
	angle = atan2(obj->radius, obj->len);
	tmp = (vec_norme(vec_init(p.x, 0, p.z)) * cos(angle)) \
		- (fabs(p.y) * sin(angle));
	tmp = fmax(tmp, (p.y));
	return (fmax(tmp, (-p.y) - obj->len));
}

double	cone_de(t_object *obj, t_vec3 p)
{
	double		angle;
	double		tmp;
	int			b;

	b = 0;
	if (obj->len <= 0 && (b = 1))
		obj->len = 1;
	angle = atan2(obj->radius, obj->len);
	tmp = (vec_norme(vec_init(p.x, 0, p.z)) * cos(angle)) \
		- (fabs(p.y) * sin(angle));
	return (tmp);
}
