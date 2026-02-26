
#ifndef CUB3D_H
#define CUB3D_H

# define BUFFER_SIZE 10
#define WIN_HEIGHT 720 // "random numbers", but dont want it to be too big
#define WIN_WIDTH 1280 // 1280 * 720 * 4 bytes = ~3.5 MB of RAM, good CPU

#include <fcntl.h>		// open, close
#include <unistd.h>		// read, write
#include <stdio.h>		// printf, perror, strerror
#include <stdlib.h>		// malloc, free, exit
#include <sys/time.h>	// gettimeofday
#include <stdbool.h>

#include <MLX42/MLX42.h>
#include "libft.h"

#include "input.h"

typedef struct s_map
{
	char **grid;
	int width;
	int height;
	int player_x;
	int player_y;
	int player_count;
	char *pending_line;
} t_map;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x; // direction vector
	double dir_y;
	double plane_x; // camera plane (perpendicular to dir)
	double plane_y;
} t_player;

typedef struct s_textures
{
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	mlx_texture_t	*north_wall;
	mlx_texture_t	*south_wall;
	mlx_texture_t	*east_wall;
	mlx_texture_t	*west_wall;
	int				*floor_color; // RGB array, one int for each color
	int				*ceil_color;
} t_textures;

typedef struct s_game
{
	mlx_t		*mlx;		// miniLibX pointer
	mlx_image_t	*img;		// *win and *img in one
	t_map		*map;		// parsed map data
	t_textures	*textures;	// loaded texture data
	t_player	*player;	// player position/direction
	int			**buffer;	// pixel buffer for rendering
} t_game;

// cleanup_game.c
void	cleanup_textures(t_textures *textures);
void	cleanup_map(t_map *map);
void	cleanup_game(t_game *game);

// close_game.c
void	close_game(void *param);

// errors.c
int	error_msg(char *str);

// init_game.c
int	init_game(t_game *game);
int	set_direction(t_player *player, char spawn);
int	init_textures(t_game *game);
int	init_player(t_game *game);

// init_structs.c
int	init_structs(t_game *game);

// parse_file.c
int	only_map_chars(char *line);
int	correct_extension(char *path, char *ext, int ext_len);
int	parse_header(int fd, t_game *game);
int	parse_map(int fd, t_game *game);
int	parse_file(char *path, t_game *game);

// parse_header.c
int	parse_texture(char *line, char **texture_path, int i);
int	valid_color_input(char *line, int **color, int i, int j);
int	parse_color(char *line, int **color, int i);
int	validate_header(t_game *game);
int	parse_header_line(char *line, t_game *game);

// parse_map.c
int	append_line(t_map *map, char *line);
int	collect_map_lines(int fd, t_game *game);
int	validate_map_chars(t_game *game);
int	is_open(t_map *map, int y, int x);
int	validate_map_closed(t_game *game);

// utils.c
char	*mini_gnl(int fd);

#endif