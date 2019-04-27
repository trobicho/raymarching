/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:48:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/27 06:49:42 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_MLX
# define INIT_MLX

#include "camera.h"

typedef struct	s_mymlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			w;
	int			h;
	int			ray_w;
	char		*buf;
	int			bpp;
	int			sline;
	int			endian;
	t_cam		cam;
}				t_mymlx;

int	init_mlx(t_mymlx *init, int w, int h, char *name);
#endif
