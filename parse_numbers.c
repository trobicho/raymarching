/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:05:04 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/10 17:44:45 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "vector.h"

double		*ft_process_points(char **str, int num, int *res)
{
	char		**s;
	char		*tmp;
	double		*d;
	int			i;

	if (ft_strarrlen(str) != num && !(*res = 0))
		return (0);
	s = str;
	if (num != 1)
	{
		tmp = s[0];
		s[0] = ft_strdup(s[0] + 1);
		free(tmp);
		s[num - 1][ft_strlen(s[num - 1]) - 1] = 0;
	}
	if (!ft_strarrtrim(s) && (*res = -1))
		return (0);
	if (!(d = (double*)malloc(sizeof(double) * (num))) \
			&& (*res = -1))
		return (0);
	i = -1;
	while (++i < num)
		d[i] = ft_atof(s[i]);
	return (d);
}

int			ft_parse_3points(char *s1, char *line, t_vec3 *vec)
{
	char		**s;
	char		**sc;
	int			ret;
	t_vec3		v;
	double		*d;

	if (!s1 || !line || !(s = ft_strsplit(line, ':')))
		return (-1);
	if ((ret = ft_process_strarr(s, s1, 3)) < 1)
		return (ret);
	if (!(sc = ft_strsplit(s[1], ',')) \
			|| !(d = ft_process_points(sc, 3, &ret)))
		return (!sc ? -1 : ret);
	v = (t_vec3){d[0], d[1], d[2]};
	if (vec)
		*vec = v;
	free(d);
	ft_strarrdel(&sc);
	ft_strarrdel(&s);
	return (1);
}

int			ft_parse_2points(char *s1, char *line, t_vec2 *vec)
{
	char			**s;
	char			**sc;
	int				ret;
	double			*d;
	t_vec2			v;

	if (!s1 || !line || !(s = ft_strsplit(line, ':')))
		return (-1);
	if ((ret = ft_process_strarr(s, s1, 2)) < 1)
		return (ret);
	if (!(sc = ft_strsplit(s[1], ',')) \
			|| !(d = ft_process_points(sc, 2, &ret)))
		return (!sc ? -1 : ret);
	v = (t_vec2){d[0], d[1]};
	if (vec)
		*vec = v;
	free(d);
	ft_strarrdel(&sc);
	ft_strarrdel(&s);
	return (1);
}

int			ft_parse_1point(char *s1, char *line, int hex, void *val)
{
	char			**s;
	char			**sc;
	int				ret;
	double			*d;

	d = 0;
	sc = 0;
	if (!s1 || !line || !(s = ft_strsplit(line, ':')))
		return (-1);
	if ((ret = ft_process_strarr(s, s1, 1)) < 1)
		return (ret);
	if (!hex && (!(sc = ft_strsplit(s[1], ',')) \
			|| !(d = ft_process_points(sc, 1, &ret))))
		return (!sc ? -1 : ret);
	if (!hex && (ret = 1) && val)
		*((double*)val) = d[0];
	else if (hex)
		ret = ft_parse_hex(s, (t_vec3*)val);
	if (d)
		free(d);
	ft_strarrdel(sc ? &sc : 0);
	ft_strarrdel(&s);
	return (ret);
}

int			ft_parse_string(char *s1, char **l, char **name)
{
	char			**s;
	char			*line;

	if (!name || !l || !(line = *l) || !s1 \
			|| !line || !(s = ft_strsplit(line, ':')))
		return (-1);
	if (ft_strarrlen(s) != 2 || !ft_strarrtrim(s) || ft_strcmp(s1, s[0]))
		return (0);
	*name = ft_strdup(s[1]);
	ft_strarrdel(&s);
	ft_strdel(l);
	return (1);
}
