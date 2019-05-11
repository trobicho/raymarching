/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:06:25 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/10 21:05:29 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_transform(char *line, t_object *obj)
{
	int			ret;
	t_vec3		trans;
	int			is_rot;

	is_rot = 0;
	ret = 0;
	if (!ft_strncmp(line, "rotate", 6) \
			&& ((ret = ft_parse_3points("rotate", line, &trans)) < 1 \
			|| !(is_rot = 1)))
		return (ret);
	else if (!ret && !ft_strncmp(line, "translate", 9) \
			&& (ret = ft_parse_3points("translate", line, &trans)) < 1)
		return (ret);
	else if (!ret && !ft_strncmp(line, "scale", 5) \
			&& ((ret = ft_parse_1point("scale", line, 0, &(obj->scale)))) < 1)
		return (ret);
	else if (!ret)
		return (0);
	if (is_rot)
		calc_transform(obj, trans.x, trans.y, trans.z);
	else
		obj->pos = vec_add(obj->pos, trans);
	return (1);
}

int			ft_parse_transform(const int fd, t_object *obj)
{
	char		*line;
	int			ret;

	if ((ret = ft_process_line(fd, &line)) < 1 || ft_strcmp_rm("{", &line))
		return (ret == 1 ? 0 : ret);
	while ((ret = ft_skip_comments(fd, &line)) > 0 && ft_strcmp("}", line))
	{
		if ((ret = ft_transform(line, obj)) < 1)
			return (ret);
		free(line);
	}
	if (ret == 1 && !ft_strcmp_rm("}", &line))
		return (1);
	return (ret);
}
