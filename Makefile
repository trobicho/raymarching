# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/11 16:16:52 by trobicho          #+#    #+#              #
#    Updated: 2019/05/12 20:41:45 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

GNL = parse.c get_next_line.c parse_helper.c parse_cam.c parse_numbers.c parse_object.c ft_strarr.c ft_col_to_int.c parse_transform.c ft_atof.c ft_normalize_ele.c ft_clamp.c

SRCS = key.c render.c thread_utils.c camera.c ray.c light.c light_utils.c marching.c scene.c transform.c operator.c csg.c de.c shape.c mandelbulb.c sierpinski.c vector.c vector_utils.c quaternion.c init_mlx.c pixel.c scene_free.c

HDRS = key.h camera.h render.h ray.h light.h marching.h scene.h de.h transform.h csg.h vector.h quaternion.h init_mlx.h pixel.h scene_free.h get_next_line.h parse.h

OUTS = $(SRCS:.c=.o) $(GNL:.c=.o)
NAME = rtv1


all: $(NAME)

$(NAME): $(OUTS)
	make -C libft
	$(CC) $(OUTS) $(CFLAGS) -lm -lmlx -lpthread -framework OpenGL -framework AppKit -Ofast -o $(NAME) -lft -Llibft

parse: $(OUTS)
	make -C libft
	$(CC) $(GNL) $(CFLAGS) -o $(NAME) -lft -Llibft

%.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	make -C libft clean
	rm -f $(OUTS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
