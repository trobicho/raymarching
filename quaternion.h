/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 02:02:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 03:38:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

typedef struct	s_quaternion
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_quaternion;

double			quat_length(t_quaternion q);
t_quaternion	quat_normalize(t_quaternion q);
t_quaternion	quat_conjug(t_quaternion q);
t_quaternion	quat_mul(t_quaternion q1, t_quaternion q2);
#endif
