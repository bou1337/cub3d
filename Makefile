NAME = cub3d
CC = gcc
FLAGS =-Wall -Wextra -Werror
MLX = -lmlx -lXext -lX11 -lm

SRCS = main.c  init.c intr.c  player.c util.c cast_ray.c draw.c exit.c handel_key.c draw_map.c free.c parser/parser1.c parser/parser2.c parser/parser3.c parser/parser4.c parser/parser5.c parser/parser6.c \
		parser/parser7.c parser/parser8.c parser/parser9.c parser/paser10.c parser/parser11.c check.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(MLX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all