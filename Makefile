NAME      = cub3D
OS       ?= $(shell uname -s)
CC        = cc

SRC_DIR   = src
OBJ_DIR   = obj
INC_DIR   = include
LIBFT_DIR = libft

ifeq ($(OS),Linux)
	MLX_DIR   = minilibx_linux
	MLX_LIB   = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm
	OS_DEF    = -D CUB3D_LINUX
else
	MLX_DIR   = minilibx_macos
	MLX_LIB   = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -framework Metal -framework MetalKit -framework AppKit
	OS_DEF    = -D CUB3D_MACOS
endif

INCLUDES  = -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)
CFLAGS    = -Wall -Wextra -Werror -g $(INCLUDES) $(OS_DEF)

SRCS      = main.c
OBJS      = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT     = $(LIBFT_DIR)/libft.a
LDLIBS    = -L $(LIBFT_DIR) -lft $(MLX_FLAGS)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
