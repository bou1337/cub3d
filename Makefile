NAME = cub3d
CC = gcc
MLX = -lmlx -lXext -lX11 -lm

SRCS = main.c  init.c intr.c  player.c util.c cast_ray.c draw.c exit.c handel_key.c draw_map.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(MLX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
