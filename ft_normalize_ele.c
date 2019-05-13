/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_ele.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 21:08:42 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/13 16:18:26 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void			ft_normalize_cam_ele(t_cam *cam, t_scene *s)
{
	cam->dir = vec_normalize(cam->dir);
	cam->up = vec_normalize(cam->up);
	cam->right = vec_normalize(cam->right);
	ft_clamp(&(s->ambient), 0, 1);
}

int				ft_normalize_obj_ele(t_object *obj)
{
	ft_clamp(&(obj->mirror), 0, 1);
	ft_clamp(&(obj->ks), 0, 1);
	return (1);
}

int				ft_parse_common(char *line, t_object *obj, char *name)
{
	int				ret;

	ret = 0;
	if (!ft_strncmp(line, "normal", 6) \
			&& (ret = ft_parse_3points("normal", line, &(obj->normal))) < 1)
		return (ft_give_error(&name, 0, ret));
	else if (!ft_strncmp(line, "reflection", 10) \
			&& (ret = ft_parse_1point("reflection", line\
					, 0, &(obj->mirror))) < 1)
		return (ft_give_error(&name, 0, ret));
	else if (!ft_strncmp(line, "length", 6) \
			&& (ret = ft_parse_1point("length", line, 0, &(obj->len))) < 1)
		return (ft_give_error(&name, 0, ret));
	else if (!ft_strncmp(line, "ks", 2) \
			&& (ret = ft_parse_1point("ks", line, 0, &(obj->ks))) < 1)
		return (ft_give_error(&name, 0, ret));
	else if (!ret && (ret = ft_parse_common2(line, obj, name)) < 1)
		return (ret);
	return (1);
}

int				ft_parse_common2(char *line, t_object *obj, char *name)
{
	int				ret;

	ret = 0;
	if (!ft_strncmp(line, "radius", 5) \
			&& (ret = ft_compute_radius(line, name, obj)) < 1)
		return (ft_give_error(&name, 0, ret));
	else if (!ft_strncmp(line, "color", 5) \
			&& (ret = ft_parse_1point("color", line, 1, &(obj->color))) < 1)
		return (ft_give_error(&name, 0, ret));
	else if (!ft_strncmp(line, "specular", 8) \
			&& (ret = ft_parse_1point("specular", line, 0, &(obj->spec))) < 1)
		return (ft_give_error(&name, 0, ret));
	else if (!ret)
		return (ft_give_error(&name, 0, ret));
	return (1);
}
