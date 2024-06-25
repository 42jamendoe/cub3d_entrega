NAME = cub3D
LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCD = ./src

SRC = cub3d.c \
	init_cub3d.c \
	exit.c \
	scene.c \
	scene_utils.c \
	player.c \
	check_map.c \
	init_mlx.c \
	textures.c \
	move.c \
	handler.c \
	raycast.c \

OBJ = $(SRC:%.c=$(SRCD)/%.o)

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -Lmlx -lmlx -lbsd -lXext -lX11 -lm -o $(NAME)

$(LIBFT):	
	$(MAKE) -C libft

$(MLX):	
	$(MAKE) -C mlx

$(SRCD)/%.o: $(SRCD)/%.c
	$(CC) $(CFLAGS) -Imlx -Iincludes -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all libft clean fclean re