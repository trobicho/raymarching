/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:13:26 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/13 13:59:24 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_lstpluck(t_list **alst, const int fd)
{
	t_list	*ptr;
	t_list	*ptr1;

	if (!*alst)
		return (0);
	ptr = *alst;
	if ((int)ptr->content_size == fd && (*alst = ptr->next) == ptr->next)
		return (ptr);
	ptr1 = ptr;
	ptr = ptr->next;
	while (ptr)
	{
		if ((int)ptr->content_size == fd)
		{
			ptr1->next = ptr->next;
			return (ptr);
		}
		ptr1 = ptr;
		ptr = ptr->next;
	}
	return (0);
}

static int		ft_lst(t_list **alst, t_list **ele, const int fd, char *str)
{
	if (!*ele)
	{
		if (!(*ele = ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1))))
			return (-1);
		free(str);
		(*ele)->content_size = fd;
		ft_lstadd(alst, *ele);
		return (1);
	}
	(*ele)->content_size = 0;
	(*ele)->next = 0;
	free((*ele));
	*ele = 0;
	return (1);
}

static int		ft_find_nl(char *str, char **line, char **extra)
{
	char	*nl;
	int		len;

	*line = 0;
	*extra = 0;
	if (!str)
		return (0);
	if (!(nl = ft_strchr(str, '\n')))
		return (0);
	len = nl - str + 1;
	if (!(*line = ft_strsub(str, 0, len - 1)))
		return (-1);
	if (*(nl + 1) == '\0')
	{
		free(str);
		return (1);
	}
	if (!(*extra = ft_strsub(str, len, ft_strlen(str) - len)))
		return (-1);
	free(str);
	return (2);
}

static int		ft_find_line(const int fd, char *tmp, char **line, t_g_inf inf)
{
	int			result;
	char		*buf;
	char		*str;

	if (inf.deep <= 0)
		return (-1);
	if ((result = ft_find_nl(tmp, line, inf.extra)) != 0)
		return (result);
	buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	result = read(fd, buf, BUFF_SIZE);
	if (result < 1)
	{
		free(buf);
		if (result == 0 && tmp && (*line = tmp))
			return (1);
		return (result);
	}
	buf[result] = '\0';
	if (!(str = ft_strjoin(tmp, buf)))
		return (-1);
	free(buf);
	free(tmp);
	inf.deep -= 1;
	return (ft_find_line(fd, str, line, inf));
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*ele;
	char			*str;
	char			*extra;
	t_g_inf			inf;

	if (fd < 0 || !line || read(fd, *line, 0) < 0)
		return (-1);
	*line = 0;
	extra = 0;
	ele = 0;
	ele = ft_lstpluck(&head, fd);
	str = ele ? (char*)ele->content : 0;
	inf.extra = &extra;
	inf.deep = 1000;
	inf.result = ft_find_line(fd, str ? str : 0, line, inf);
	if (ele)
		ft_lst(&head, &ele, 0, 0);
	ele = 0;
	if (inf.result == 0 || inf.result == -1)
		return (inf.result);
	if (inf.result == 2)
		if (!(ft_lst(&head, &ele, fd, extra)))
			return (-1);
	return (1);
}
