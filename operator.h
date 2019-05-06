/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:37:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/05 22:06:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H
#include "scene.h"

double	csg_sub(t_object *obj, t_vec3 p);
double	csg_union(t_object *obj, t_vec3 p);
double	csg_intersect(t_object *obj, t_vec3 p);
#endif
