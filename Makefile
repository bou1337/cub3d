NAME = cub3d
CC = gcc
//CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -lX11 -lXext 

SRCS = main.c  draw.c  hook.c utlis.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(MLX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
