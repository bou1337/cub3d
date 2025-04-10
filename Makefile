NAME = cub3d
CC = gcc
MLX = -lmlx -lXext -lX11 -lm

SRCS = main.c  init.c  util.c  check.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
