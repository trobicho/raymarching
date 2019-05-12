/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:13:36 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/12 21:07:34 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char		*ft_atof_i(char *str, double *sum, int *j, int fi)
{
	int			i;
	int			is_negative;

	*sum = 0;
	i = 0;
	is_negative = 0;
	if (fi)
	{
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str = str + 1;
		if (*str == '-' || *str == '+')
			if (*(str++) == '-')
				is_negative = 1;
	}
	while (str[i] != '\0' && ((str[i] >= '0' && str[i] <= '9')))
		*sum = (*sum * 10) + (str[i++] - '0');
	if (j)
		*j = i;
	if (is_negative == 1)
		*sum = *sum * -1;
	return (str + i);
}

double		ft_atof(char *s)
{
	char		*str;
	double		sum_i;
	double		sum_f;
	int			j;

	str = ft_atof_i(s, &sum_i, 0, 1);
	j = 0;
	if (!*str || *str != '.')
		return (sum_i);
	ft_atof_i(str + 1, &sum_f, &j, 0);
	sum_i = sum_i + ((sum_f / pow(10, j)) * (sum_i < 0 ? -1 : 1));
	return (sum_i);
}
