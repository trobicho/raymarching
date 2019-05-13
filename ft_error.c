/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:46:19 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/13 16:10:05 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			ft_give_error(char **line, t_mymlx *ml, int ret)
{
	if (ml)
		ft_del_scene(&(ml->scene));
	ft_strdel(line);
	return (ret);
}

void		ft_del_scene(t_scene *s)
{
	if (!s)
		return ;
	ft_del_light(&(s->l_light));
	ft_del_obj(&(s->l_obj));
}

void		ft_del_light(t_list_light **light)
{
	t_list_light		*tmp;
	t_list_light		*tmp1;

	if (!light)
		return ;
	tmp = *light;
	while (tmp)
	{
		tmp1 = tmp->next;
		free(tmp);
		tmp = tmp1;
	}
	*light = 0;
}

void		ft_del_obj(t_list_obj **obj)
{
	t_list_obj			*tmp;
	t_list_obj			*tmp1;

	if (!obj)
		return ;
	tmp = *obj;
	while (tmp)
	{
		tmp1 = tmp->next;
		free(tmp);
		tmp = tmp1;
	}
	*obj = 0;
}
