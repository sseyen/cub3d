
#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <fcntl.h>		// open, close
#include <unistd.h>		// read, write
#include <stdio.h>		// printf, perror, strerror
#include <stdlib.h>		// malloc, free, exit
#include <sys/time.h>	// gettimeofday
#include <stdbool.h>

#include "libft.h"
#include <MLX42/MLX42.h>

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
	char *north_path;
	char *south_path;
	char *east_path;
	char *west_path;
	void *north_wall;
	void *south_wall;
	void *east_wall;
	void *west_wall;
	int *floor_color; // RGB array, one int for each color
	int *ceil_color;
	int width;
	int height;
} t_textures;

typedef struct s_game
{
	void *mlx;			  // miniLibX pointer
	void *win;			  // window pointer
	t_map *map;			  // parsed map data
	t_player *player;	  // player position/direction
	t_textures *textures; // loaded texture data
	int **buffer;		  // pixel buffer for rendering
} t_game;

// cleanup_game.c
void	cleanup_textures(t_textures *textures);
void	cleanup_map(t_map *map);
void	cleanup_game(t_game *game);

// errors.c
int	error_msg(char *str);

// init_.c
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