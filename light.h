/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:20:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/01 10:00:17 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "scene.h"

t_vec3			light_calc(t_scene *scene, t_vec3 p, t_object *obj_hit, int normal);
t_vec3			get_normal(t_scene *scene, t_vec3 p); //obj direct
#endif
