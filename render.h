/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:36:45 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/09 16:53:29 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
#include "init_mlx.h"

int	render(void *param);
int	render_init(t_mymlx *ml);
int	render_close(t_mymlx *ml);
#endif
