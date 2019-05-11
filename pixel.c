/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:55:40 by trobicho          #+#    #+#             */
/*   Updated: 2019/05/11 23:04:36 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"
#include "vector.h"
#include "mlx.h"

static void	putcolor_bpp(char *buf, int bpp, unsigned int color)
{
	int		b;
	char	*c;

	b = 0;
	c = (char*)&color;
	while (b < bpp)
	{
		buf[b] = c[b];
		b++;
	}
}

void		putpixel(t_mymlx *ml, int x, int y, unsigned int color)
{
	putcolor_bpp(&ml->buf[x * ml->bpp + y * ml->sline], ml->bpp, color);
}

void		putpixel_w(t_mymlx *ml, t_pixw p, unsigned int color)
{
	int	wc;
	int	hc;
	int	of;

	wc = 0;
	while (wc < p.w && p.x + wc < ml->w)
	{
		hc = 0;
		while (hc < p.w && p.y + hc < ml->h)
		{
			of = (p.x + wc) * ml->bpp + (p.y + hc) * ml->sline;
			putcolor_bpp(&ml->buf[of], ml->bpp, color);
			hc++;
		}
		wc++;
	}
}

void		putpixel_vec_w(t_mymlx *ml, t_pixw p, t_vec3 vc)
{
	unsigned int	color;
	unsigned char	c[3];

	vc.x = (vc.x > 1.0) ? 1.0 : vc.x;
	vc.y = (vc.y > 1.0) ? 1.0 : vc.y;
	vc.z = (vc.z > 1.0) ? 1.0 : vc.z;
	c[0] = 255 * vc.x;
	c[1] = 255 * vc.y;
	c[2] = 255 * vc.z;
	color = (c[0] << 16) | (c[1] << 8) | c[2];
	putpixel_w(ml, p, color);
}
