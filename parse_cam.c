/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:43:02 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/11 03:06:07 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			ft_parse_cam_ele(char **line, t_mymlx *ml, char **name, t_vec2 *dim)
{
	int			ret;

	ret = 0;
	if (!ft_strncmp("name", *line, 4))
		return ((ret = ft_parse_string("name", line, name) < 1 ? ret : 0b0001));
	else if (!ft_strncmp("origin", *line, 6))
		return ((ret = ft_parse_3points("origin", *line, &(ml->cam.pos)) < 1 \
					? ret : 0b0000010));
	else if (!ft_strncmp("direction", *line, 9))
		return ((ret = ft_parse_3points("direction", *line\
						, &(ml->cam.dir)) < 1 ? ret : 0b0000100));
	else if (!ft_strncmp("up", *line, 2))
		return ((ret = ft_parse_3points("up", *line\
						, &(ml->cam.up))) < 1 ? ret : 0b0001000);
	else if (!ft_strncmp("right", *line, 5))
		return ((ret = ft_parse_3points("right", *line\
						, &(ml->cam.right))) < 1 ? ret : 0b0010000);
	else if (!ft_strncmp("ambient", *line, 5))
		return ((ret = ft_parse_1point("ambient", *line, 0\
						, &(ml->scene.ambient))) < 1 ? ret : 0b0100000);
	else if (!ft_strncmp("screen", *line, 6))
		return ((ret = ft_parse_2points("screen", *line, dim) < 1 \
					? ret : 0b1000000));
	else
		return (0);
}

int			ft_parse_cam(const int fd, t_mymlx *ml)
{
	char		*line;
	int			ret;
	char		*name;
	t_vec2		dim;
	int			s;

	if ((ret = ft_process_line(fd, &line)) < 1 || ft_strcmp_rm("{", &line))
		return (ret < 1 ? ret : 0);
	s = 0;
	while ((ret = ft_skip_comments(fd, &line)) > 0 && ft_strcmp("}", line))
	{
		ret = ft_parse_cam_ele(&line, ml, &name, &dim);
		if (ret < 1 || (s & ret) || !(s = s | ret))
			return (ret < 1 ? ret : 0);
		if (line)
			free(line);
	}
	if (ret < 1 || !(s & 0b1000000) || !(s & 0b001000) || !(s & 0b010000))
		return (ret == 1 ? 0 : ret);
	ft_strcmp_rm(line, &line);
	if (!ft_create_window(ml, dim.x, dim.y, s & 0b0001 ? name : 0) \
			|| (s & 0b0001 && ft_strcmp_rm(name, &name)))
		return (-1);
	ft_normalize_cam_ele(&(ml->cam), &(ml->scene));
	return (1);
}

int			ft_parse_light_ele(char *line, t_vec3 *pos, double *d, t_vec3 *col)
{
	int			ret;

	ret = 0;
	if (!ft_strncmp("origin", line, 6))
		return ((ret = ft_parse_3points("origin", line, pos)) < 1 \
				? ret : 0b001);
	else if (!ft_strncmp("intensity", line, 9))
		return ((ret = ft_parse_1point("intensity", line, 0, d)) < 1 \
				? ret : 0b010);
	else if (!ft_strncmp("color", line, 5))
		return ((ret = ft_parse_1point("color", line, 1, col)) < 1 \
				? ret : 0b100);
	else if (!ret)
		return (0);
	return (1);
}

int			ft_parse_light(const int fd, t_mymlx *ml, int ret)
{
	char		*line;
	int			s;
	t_vec3		pos;
	t_vec3		col;
	double		d;

	ret = 0;
	s = 0;
	col = (t_vec3){1, 1, 1};
	if ((ret = ft_process_line(fd, &line)) < 1 || ft_strcmp_rm("{", &line))
		return (ret < 1 ? ret : 0);
	while ((ret = ft_skip_comments(fd, &line)) > 0 && ft_strcmp("}", line))
	{
		if ((ret = ft_parse_light_ele(line, &pos, &d, &col)) < 1 || s & ret)
			return (ret == 1 ? 0 : ret);
		s = s | ret;
		ft_strdel(&line);
	}
	if (ret < 1 || (s & 0b011) != 0b011 \
			|| !scene_add_light(&(ml->scene), pos, d, col))
		return (ret == 1 ? -1 : ret);
	ft_strdel(&line);
	return (1);
}
