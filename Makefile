CC = gcc
CFLAGS = -g
#CFLAGS = -Wall -Wextra -Werror
SRCS = main.c ray.c marching.c scene.c vector.c init_mlx.c pixel.c
HDRS = ray.h marching.h scene.h vector.h init_mlx.h pixel.h
OUTS = $(SRCS:.c=.o)
NAME = marching

all: $(NAME)

$(NAME): $(OUTS)
	$(CC) $(OUTS) $(CFLAGS) -lm -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OUTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 

