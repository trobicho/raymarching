
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
