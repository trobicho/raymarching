/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:32 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/26 06:19:50 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "mlx.h"
#include "init_mlx.h"
#include "ray.h"

static void	init(t_mymlx *ml)
{
	mlx_hook(ml->win_ptr, 2, 0, &key_hook, (void*)ml);
	mlx_hook(ml->win_ptr, 17, 0, &closer, (void*)ml);
}

int	main(int ac, char **av)
{
	int	w = 600;
	int h = 600;
	t_mymlx	ml;

	if (init_mlx(&ml, w, h, "marching") == -1)
		return (-1);
	init(&ml);
	ray_scan(&ml);
	mlx_put_image_to_window(ml.mlx_ptr, ml.win_ptr, ml.img_ptr, 0, 0);
	mlx_loop(ml.mlx_ptr);
	return (0);
}
