/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:28:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/04 21:03:17 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "init_mlx.h"
# include "scene.h"

typedef struct	s_ray_inf
{
	t_vec3		r_o;
	t_vec3		r_d;
	t_vec3		p;
	double		d;
	t_object	*obj_min;
}				t_ray_inf;

int				ray_loop(void *param);
void			ray_scan(t_mymlx *ml);
#endif
