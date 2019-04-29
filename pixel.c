
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

void		putpixel_w(t_mymlx *ml, int x, int y, int w, unsigned int color)
{
	int	wc;
	int	hc;

	wc = 0;
	while (wc < w && x + wc < ml->w)
	{
		hc = 0;
		while (hc < w && y + hc < ml->h)
		{
			putcolor_bpp(&ml->buf[(x + wc)  * ml->bpp + (y + hc) * ml->sline]
				, ml->bpp, color);
			hc++;
		}
		wc++;
	}
}

void		putpixel_vec_w(t_mymlx *ml, int x, int y, int w, t_vec3 vc)
{
	int				wc;
	int				hc;
	unsigned int	color;
	unsigned char	c[3];

	c[0] = 255 * vc.x;
	c[1] = 255 * vc.y;
	c[2] = 255 * vc.z;

	color = (c[0] << 16) | (c[1] << 8) | c[2];
	wc = 0;
	while (wc < w && x + wc < ml->w)
	{
		hc = 0;
		while (hc < w && y + hc < ml->h)
		{
			putcolor_bpp(&ml->buf[(x + wc)  * ml->bpp + (y + hc) * ml->sline]
				, ml->bpp, color);
			hc++;
		}
		wc++;
	}
}
