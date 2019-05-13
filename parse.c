/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:18:47 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/13 17:20:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "render.h"
#include <stdlib.h>

int			ft_puterror(int err_no)
{
	if (!err_no)
		ft_putendl("./Rtv1 [filename]");
	else if (err_no == 1)
		ft_putendl("Incorrect Argument Number");
	else if (err_no == 2)
		ft_putendl("File Not Found");
	else if (err_no == 3)
		ft_putendl("Error");
	else if (err_no == 4)
		ft_putendl("Incorrect Syntax for input file");
	return (1);
}

int			ft_fill_scene(const int fd, t_mymlx *ml)
{
	char		*line;
	int			ret;

	if ((ret = ft_skip_comments(fd, &line)) < 1 \
				|| (!ft_strcmp("}", line) && !ft_strcmp_rm("}", &line)))
		return (0);
	if (!ft_strcmp("camera", line) && !ft_strcmp_rm("camera", &line) \
			&& (ret = ft_parse_cam(fd, ml)) < 1)
		return (ret);
	while ((ret = ft_skip_comments(fd, &line)) > 0 && ft_strcmp("}", line))
	{
		ret = 0;
		if (!ft_strcmp("light", line) && !ft_strcmp_rm("light", &line) \
				&& (ret = ft_parse_light(fd, ml, 0)) < 1)
			return (ret);
		else if (!ret && line && !ft_strcmp("object", line) \
				&& !ft_strcmp_rm("object", &line) \
				&& (ret = ft_parse_object(fd, ml)) < 1)
			return (ret);
		else if (!ret && !ft_strcmp_rm(line, &line))
			return (0);
	}
	if (ret < 1 || ft_strcmp_rm(line, &line))
		return (ret);
	return (1);
}

int			ft_parse_file(const int fd, t_mymlx *ml)
{
	int			ret;
	char		*line;

	if ((ret = ft_skip_comments(fd, &line)) < 1 || ft_strcmp_rm("scene", &line))
		return (ret == 1 ? 0 : ret);
	if ((ret = ft_process_line(fd, &line)) < 1 || ft_strcmp_rm("{", &line))
		return (ret == 1 ? 0 : ret);
	if ((ret = ft_fill_scene(fd, ml)) < 1)
		return (ret);
	if ((ret = ft_skip_comments(fd, &line)))
	{
		if (ret == 1)
			free(line);
		return (ret == 1 ? 0 : -1);
	}
	return (1);
}

int			main(int ac, char **av)
{
	int			fd;
	int			ret;
	t_mymlx		ml;

	if (ac == 1)
		return (ft_puterror(0));
	else if (ac != 2)
		return (ft_puterror(1));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (ft_puterror(2));
	if (!ft_init(&ml))
		return (ft_puterror(3));
	if ((ret = ft_parse_file(fd, &ml)) < 1)
		exit(ft_puterror(ret == -1 ? 3 : 4));
	close(fd);
	ml.ray_w = 16;
	render_init(&ml);
	mlx_put_image_to_window(ml.mlx_ptr, ml.win_ptr, ml.img_ptr, 0, 0);
	mlx_hook(ml.win_ptr, 2, 0, &key_hook, (void*)(&ml));
	mlx_hook(ml.win_ptr, 17, 0, &closer, (void*)(&ml));
	mlx_loop_hook(ml.mlx_ptr, &render, (void*)(&ml));
	mlx_loop(ml.mlx_ptr);
	return (0);
}
