/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:42:00 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/12 18:25:38 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			ft_parse_obj_name(char *name, t_vec3 pos, \
		t_mymlx *ml, t_object **obj)
{
	void			*p;

	if (!ft_strcmp("torus", name))
		p = &torus_de;
	else if (!ft_strcmp("sphere", name))
		p = &sphere_de;
	else if (!ft_strcmp("mandelblub", name))
		p = &mandelbulb_de;
	else if (!ft_strcmp("plane", name))
		p = &plane_de;
	else if (!ft_strcmp("sierpinski", name))
		p = &sierpinski_de;
	else if (!ft_strcmp("cone", name))
		p = &cone_de;
	else if (!ft_strcmp("capped cone", name))
		p = &capped_cone_de;
	else if (!ft_strcmp("cylinder", name))
		p = &cylinder_de;
	else if (!ft_strcmp("capped cylinder", name))
		p = &capped_cylinder_de;
	else
		return (0);
	if (!(*obj = scene_add_obj(&(ml->scene), pos, p)))
		return (-1);
	return (1);
}

int			ft_compute_radius(char *line, char *name, t_object *obj)
{
	int			ret;
	t_vec2		r;
	int			b;

	if (!line || !obj || !name)
		return (-1);
	ret = 0;
	b = 0;
	if ((!ft_strcmp(name, "sphere") || !ft_strcmp(name, "cone") \
				|| !ft_strcmp(name, "cylinder") \
				|| !ft_strcmp(name, "capped cylinder") \
				|| !ft_strcmp(name, "capped cone")) \
			&& (ret = ft_parse_1point("radius", line, 0, &(obj->radius))) < 1)
		return (ret);
	else if (!ret && !ft_strcmp(name, "torus") \
			&& ((ret = ft_parse_2points("radius", line, &r)) < 1 \
				|| ((obj->radius = r.x) \
					&& (obj->radius2 = r.y) && ret < 0)))
		return (ret);
	else if (!ret)
		return (0);
	return (1);
}

int			ft_parse_obj_np(const int fd, char **name, t_vec3 *pos)
{
	int			ret;
	char		*line;

	if ((ret = ft_skip_comments(fd, &line)) < 1 || ft_strncmp("name", line, 4) \
			|| (ret = ft_parse_string("name", &line, name)) < 1)
		return (ret == 1 ? 0 : ret);
	if ((ret = ft_skip_comments(fd, &line)) < 1 \
			|| ft_strncmp("position", line, 8) \
			|| (ret = ft_parse_3points("position", line, pos)) < 1)
		return (ret == 1 ? 0 : ret);
	ft_strdel(&line);
	return (1);
}

int			ft_parse_object(const int fd, t_mymlx *ml)
{
	char		*line;
	int			ret;
	char		*name;
	t_vec3		pos;
	t_object	*obj;

	if ((ret = ft_process_line(fd, &line)) < 1 || ft_strcmp_rm("{", &line))
		return (ret == 1 ? 0 : ret);
	if ((ret = ft_parse_obj_np(fd, &name, &pos)) < 1 \
			|| (ret = ft_parse_obj_name(name, pos, ml, &obj)) < 1)
		return (ret);
	while ((ret = ft_skip_comments(fd, &line)) > 0 && ft_strcmp("}", line))
	{
		ret = 0;
		if (!ft_strcmp(line, "transform") \
				&& (ret = ft_parse_transform(fd, obj)) < 1)
			return (ret);
		else if (!ret && (ret = ft_parse_common(line, obj, name)) < 1)
			return (ret);
		free(line);
	}
	if (ret == 1 && !ft_strcmp_rm("}", &line) \
			&& !ft_strcmp_rm(name, &name) && ft_normalize_obj_ele(obj))
		return (1);
	return (ret);
}
