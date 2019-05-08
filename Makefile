CC = gcc
CFLAGS = -g
#CFLAGS = -Wall -Wextra -Werror
SRCS = main.c key.c render.c camera.c ray.c light.c marching.c scene.c transform.c operator.c de.c vector.c quaternion.c init_mlx.c pixel.c scene_free.c
HDRS = key.c camera.h render.h ray.h light.h marching.h scene.h de.h transform.h operator.h vector.h quaternion.h init_mlx.h pixel.h scene_free.h
OUTS = $(SRCS:.c=.o)
NAME = rtv1

all: $(NAME)

$(NAME): $(OUTS)
	$(CC) $(OUTS) $(CFLAGS) -lm -lmlx -framework OpenGL -framework AppKit -Ofast -o $(NAME)

linux: $(OUTS)
	$(CC) $(OUTS) $(CFLAGS) -lmlx -lX11 -lXext -lm -I../42/minilibx -g -o $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -I../42/minilibx -c $^

clean:
	rm -f $(OUTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 

