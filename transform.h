/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:11:43 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/10 11:59:14 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "quaternion.h"
# include "scene.h"

double	op_transform(t_object *obj, t_vec3 p);
double	op_scale(t_object *obj, t_vec3 p);
double	op_twist(t_object *obj, t_vec3 p);
void	calc_transform(t_object *obj, double ax, double ay, double az);
#endif
