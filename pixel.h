/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:52:06 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/12 19:10:22 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_H
# define PIXEL_H
# include "init_mlx.h"
# include "vector.h"

typedef struct	s_pixw
{
	int	x;
	int	y;
	int	w;
}				t_pixw;

void			putpixel(t_mymlx *ml, int x, int y, unsigned int color);
void			putpixel_w(t_mymlx *ml, t_pixw p, unsigned int color);
void			putpixel_vec_w(t_mymlx *ml, t_pixw p, t_vec3 vc);
#endif
