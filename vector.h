/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:02:24 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/24 18:11:44 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

double			vec_norme(t_vec3 v);
t_vec3			vec_normalize(t_vec3 v);
#endif
