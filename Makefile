CC = gcc
CFLAGS = -g
#CFLAGS = -Wall -Wextra -Werror
SRCS = main.c key.c camera.c ray.c light.c marching.c scene.c transform.c operator.c de.c vector.c quaternion.c init_mlx.c pixel.c
HDRS = key.c camera.h ray.h light.h marching.h scene.h de.h transform.h operator.h vector.h quaternion.h init_mlx.h pixel.h
OUTS = $(SRCS:.c=.o)
NAME = marching

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

