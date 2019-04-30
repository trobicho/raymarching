/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   de.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:14:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/30 02:23:34 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	DE_H
# define DE_H

# include "scene.h"

double	sphere_de(t_object *obj, t_vec3 p);
double	torus_de(t_object *obj, t_vec3 p);
double	cone_de(t_object *obj, t_vec3 p);
double	mandelbulb_de(t_object *obj, t_vec3 v);
double	sierpinski_de(t_object *obj, t_vec3 v);
#endif
