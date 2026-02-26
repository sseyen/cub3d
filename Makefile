NAME       = cub3D
OS        ?= $(shell uname -s)
CC         = cc

SRC_DIR    = src
OBJ_DIR    = obj
INC_DIR    = include
LIBFT_DIR  = libft
MLX42_DIR  = MLX42
MLX42_BUILD= $(MLX42_DIR)/build
MLX42_LIB  = $(MLX42_BUILD)/libmlx42.a

ifeq ($(OS),Linux)
	GLFW_LINK ?= -ldl -lglfw -pthread -lm
else
	GLFW_PREFIX ?= /opt/homebrew
	GLFW_LINK ?= -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -L$(GLFW_PREFIX)/lib
endif

INCLUDES   = -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX42_DIR)/include
CFLAGS     = -Wall -Wextra -Werror -g $(INCLUDES) $(OS_DEF)

SRCS       = main.c \
			cleanup_game.c \
			errors.c \
			init_game.c \
			init_structs.c \
			parse_file.c \
			parse_header.c \
			parse_map.c \
			utils.c \
# 			game_loop.c \
			key_press.c \

OBJS       = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT      = $(LIBFT_DIR)/libft.a
LDLIBS     = -L $(LIBFT_DIR) -lft -L $(MLX42_BUILD) -lmlx42 $(GLFW_LINK)

all: $(NAME)


$(NAME): $(LIBFT) $(MLX42_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(MLX42_LIB):
	cmake -S $(MLX42_DIR) -B $(MLX42_BUILD) -DGLFW_FETCH=ON
	cmake --build $(MLX42_BUILD) --parallel

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d $(MLX42_BUILD) ]; then cmake --build $(MLX42_BUILD) --target clean; fi

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX42_BUILD)

re: fclean all

.PHONY: all clean fclean re
