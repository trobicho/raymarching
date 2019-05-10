/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:40:36 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/06 14:14:29 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			ft_conv_hex(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (ch - '0');
	else if (ch >= 'a' && ch <= 'f')
		return (10 + (ch - 'a'));
	else
		return (-1);
}

int			ft_col_to_int(char *hex, int *col)
{
	int				d;
	int				tmp;

	d = 0;
	if (!col || !hex || ft_strlen(hex) != 2)
		return (-1);
	if ((d = ft_conv_hex(hex[1])) == -1)
		return (0);
	if ((tmp = ft_conv_hex(hex[0])) == -1)
		return (0);
	d = (tmp * 16) + d;
	*col = d;
	return (1);
}
