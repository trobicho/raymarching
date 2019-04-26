/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 02:00:32 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 03:58:02 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

typedef struct	s_cam
{
	t_vec3	dir;
	t_vec3	pos;
}				t_cam;

void			cam_translate(t_cam *cam, t_vec3 v);
void			cam_rotate(t_cam *cam, double angle, t_vec3 v);
#endif
