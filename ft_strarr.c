/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:29:48 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/10 17:45:36 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int				ft_strarrlen(char **s)
{
	int			len;

	if (!s)
		return (0);
	len = 0;
	while (*(s++))
		len = len + 1;
	return (len);
}

int			ft_strarrtrim(char **str)
{
	char		**s;
	char		*tmp;

	s = str;
	if (!s)
		return (0);
	while (*s)
	{
		tmp = *s;
		if (!(*s = ft_strtrim(tmp)))
			return (0);
		free(tmp);
		s = s + 1;
	}
	return (1);
}

void		ft_strarrdel(char ***s)
{
	char		**str;

	if (!s || !*s)
		return ;
	str = *s;
	while (*str)
		ft_strdel(str++);
	free(*s);
	*s = 0;
}

int			ft_process_strarr(char **str, char *s1, int num)
{
	char		**s;

	s = str;
	if (!(ft_strarrtrim(s)))
		return (-1);
	if (ft_strarrlen(s) != 2 || ft_strcmp(s1, s[0]))
		return (0);
	if (num != 1 && (s[1][0] != '(' \
				|| s[1][ft_strlen(s[1]) - 1] != ')'))
		return (0);
	return (1);
}
