NAME = cub3d
CC = gcc
//CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -lXext -lX11 -lm

SRCS = main.c  draw.c  hook.c utlis.c draw_line.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(MLX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
