/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:25:19 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/10 11:26:34 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSG_H
# define CSG_H 

# include "scene.h"

double	csg_sub(t_object *obj, t_vec3 p);
double	csg_union(t_object *obj, t_vec3 p);
double	csg_intersect(t_object *obj, t_vec3 p);
#endif
