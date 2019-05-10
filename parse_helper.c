/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:49:34 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/09 01:38:14 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		ft_tolowercase(char *str)
{
	int			i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
}

int			ft_strcmp_rm(char *s1, char **line)
{
	int			ret;

	ret = ft_strcmp(s1, *line);
	ft_strdel(line);
	return (ret);
}

int			ft_process_line(const int fd, char **line)
{
	int			ret;
	char		*tmp;

	if (!line)
		return (-1);
	if ((ret = get_next_line(fd, line)) < 1)
		return (ret);
	if (!(tmp = ft_strtrim(*line)))
		return (-1);
	free(*line);
	ft_tolowercase(tmp);
	*line = tmp;
	return (1);
}

int			ft_skip_comments(const int fd, char **line)
{
	int			ret;
	char		*tmp;

	while ((ret = ft_process_line(fd, &tmp)) > 0)
	{
		if (!(!tmp[0] || tmp[0] == '#') && (*line = tmp))
			return (1);
		free(tmp);
	}
	return (ret);
}

int			ft_parse_hex(char **s, t_vec3 *val)
{
	int			ret;
	char		*t;
	int			c[3];

	if (ft_strlen(s[1]) == 8 && (t = s[1]))
	{
		if (s[1][0] != '0' && s[1][1] != 'x')
			return (0);
		if (!(s[1] = ft_strdup(s[1] + 2)))
			return (-1);
		ft_strdel(&t);
	}
	if (ft_strlen(s[1]) != 6)
		return (0);
	if (!(t = ft_strnew(2)))
		return (1);
	if ((ret = ft_col_to_int(ft_strncpy(t, s[1], 2), &(c[0]))) < 1 \
			|| (ret = ft_col_to_int(ft_strncpy(t, s[1] + 2, 2), &(c[1]))) < 1 \
			|| (ret = ft_col_to_int(ft_strncpy(t, s[1] + 4, 2), &(c[2]))) < 1)
		return (ret);
	*val = (t_vec3){((double)c[0] / 255)\
			, ((double)c[1] / 255), ((double)c[2] / 255)};
	ft_strdel(&t);
	return (1);
}
