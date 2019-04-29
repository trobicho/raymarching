/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:20:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/29 03:56:15 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef struct	s_light
{
	t_vec3	pos;
	double	intensity;
}				t_light;

t_vec3			light_calc(t_light light, t_vec3 p, int normal);
t_vec3			get_normal(t_vec3 p);
#endif
