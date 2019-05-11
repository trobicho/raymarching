/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:35:29 by dkhatri           #+#    #+#             */
/*   Updated: 2019/05/11 03:05:51 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "get_next_line.h"
# include "transform.h"
# include "vector.h"
# include "init_mlx.h"
# include "de.h"
# include "ray.h"
# include "mlx.h"
# include "key.h"
# include "scene.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

void			ft_tolowercase(char *str);
int				ft_strcmp_rm(char *s1, char **line);
int				ft_process_line(const int fd, char **line);
int				ft_skip_comments(const int fd, char **line);
int				ft_parse_cam(const int fd, t_mymlx *ml);
int				ft_parse_light(const int fd, t_mymlx *ml, int ret);
int				ft_parse_object(const int fd, t_mymlx *ml);
int				ft_parse_transform(const int fd, t_object *obj);

int				ft_parse_3points(char *s1, char *line, t_vec3 *vec);
int				ft_parse_2points(char *s1, char *line, t_vec2 *vec);
int				ft_parse_1point(char *s1, char *line, int hex, void *val);
int				ft_parse_string(char *s1, char **line, char **name);

int				ft_strarrlen(char **s);
int				ft_strarrtrim(char **str);
void			ft_strarrdel(char ***s);
int				ft_process_strarr(char **str, char *s1, int num);

int				ft_col_to_int(char *hex, int *col);
int				ft_parse_common(char *line, t_object *obj, char *name);
int				ft_parse_common2(char *line, t_object *obj, char *name);
int				ft_parse_hex(char **s, t_vec3 *val);
double			ft_atof(char *s);
void			ft_clamp(double *d, double start, double end);
void			ft_normalize_cam_ele(t_cam *cam, t_scene *s);
int				ft_normalize_obj_ele(t_object *obj);
int				ft_compute_radius(char *line, char *name, t_object *obj);

#endif
