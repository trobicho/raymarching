/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:18:16 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 19:19:10 by trobicho         ###   ########.fr       */
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

	t = (t_vec3){obj->radius, obj->radius2, 0.0};
	p_tmp = (t_vec3){p.x, 0.0, p.z};
	q = (t_vec3){vec_norme(p_tmp) - t.x, p.y, 0.0};
	return (vec_norme(q) - t.y);
}

double	cone_de(t_object *obj, t_vec3 p)
{
	t_vec3	q;
	double	d1;
	double	d2;
	double	d1t;
	double	d2t;
	t_vec3	c;

	q = (t_vec3){vec_norme((t_vec3){p.x, p.y, 0.0}), p.y, 0.0};
	c = vec_normalize((t_vec3){obj->radius, obj->len, 0.0});
	d1 = -q.y - 1.0;
	d2 = fmax(vec_dot(q, c), q.y);
	d1t = d1;
	d2t = d2;
	if (d1 < 0 || d2 < 0)
	{
		d1t = 0.0;
		d2t = 0.0;
	}
	return (vec_norme((t_vec3){d1t, d2t, 0.0}) + fmin(fmax(d1, d2), 0.0));
}
