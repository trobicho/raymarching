/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:52:06 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/27 06:25:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIXEL_H
# define PIXEL_H
#include "init_mlx.h"

void	putpixel(t_mymlx *ml, int x, int y, unsigned int color);
void	putpixel_w(t_mymlx *ml, int x, int y, int w, unsigned int color);
#endif
