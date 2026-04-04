/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:08:03 by alisseye          #+#    #+#             */
/*   Updated: 2026/04/04 12:11:38 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 10
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# include <fcntl.h>		// open, close
# include <math.h>		// floor, fabs
# include <unistd.h>	// read, write
# include <stdio.h>		// printf, perror, strerror
# include <stdlib.h>	// malloc, free, exit
# include <sys/time.h>	// gettimeofday
# include <stdbool.h>	// bool type

# include <MLX42/MLX42.h>

# include "input.h"
# include "libft.h"

typedef mlx_texture_t	*t_texptr;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		player_count;
	char	*pending_line;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

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
	int				*floor_color;
	int				*ceil_color;
}	t_textures;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_textures	*textures;
	t_player	*player;
	int			**buffer;
}	t_game;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* cleanup_game.c */
void		cleanup_textures(t_textures *textures);
void		cleanup_map(t_map *map);
void		cleanup_game(t_game *game);

/* close_game.c */
void		close_game(void *param);

/* errors.c */
int			error_msg(char *str);

/* game_loop.c */
void		game_loop(void *param);

/* handle_movement.c */
void		move_forward_back(t_player *p, t_map *map, int forward);
void		move_side(t_player *p, t_map *map, int right);
void		rotate_player(t_player *p, int right);
void		handle_movement(t_game *game);

/* init_game.c */
int			init_game(t_game *game);
int			set_direction(t_player *player, char spawn);
int			init_textures(t_game *game);
int			init_player(t_game *game);

/* init_structs.c */
int			init_structs(t_game *game);

/* key_press.c */
void		key_press(mlx_key_data_t keydata, void *param);

/* parse_file.c */
int			only_map_chars(char *line);
int			correct_extension(char *path, char *ext, int ext_len);
int			parse_header(int fd, t_game *game);
int			parse_map(int fd, t_game *game);
int			parse_file(char *path, t_game *game);

/* parse_header.c */
int			parse_texture(char *line, char **texture_path, int i);
int			valid_color_input(char *line, int **color, int i, int j);
int			parse_color(char *line, int **color, int i);
int			validate_header(t_game *game);
int			parse_header_line(char *line, t_game *game);

/* parse_map.c */
int			append_line(t_map *map, char *line);
int			collect_map_lines(int fd, t_game *game);
int			validate_map_chars(t_game *game);
int			is_open(t_map *map, int y, int x);
int			validate_map_closed(t_game *game);

/* raycasting.c */
void		raycasting_math(t_game *game);
void		get_ray_direction(t_ray *ray, t_player *p, int x);
void		calc_step_distance(t_ray *ray, t_player *p);
void		find_nearest_wall(t_ray *ray, t_map *map);
void		calc_wall_height(t_ray *ray);

/* render.c */
void		draw_column(t_game *game, t_ray *ray, int x);
void		draw_ceiling(t_game *game, t_ray *ray, int x);
void		draw_floor(t_game *game, t_ray *ray, int x);
void		draw_wall(t_game *game, t_ray *ray, int x);
int			get_tex_offset(t_ray *ray, t_player *p);

/* texture.c */
t_texptr	get_wall_texture(t_game *game, t_ray *ray);
uint32_t	get_tex_color(mlx_texture_t *tex, int tex_x, int tex_y);
uint32_t	rgb_to_color(int *rgb);

/* utils.c */
char		*mini_gnl(int fd);

#endif
