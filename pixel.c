
#include "pixel.h"
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
