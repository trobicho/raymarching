/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:36:45 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/11 16:27:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "init_mlx.h"

void	*ray_thread(void *param);
int		render(void *param);
int		render_init(t_mymlx *ml);
int		render_close(t_mymlx *ml);
void	wake_up(t_mymlx *ml);
int		thread_unlockn(t_mymlx *ml, int n);
#endif
