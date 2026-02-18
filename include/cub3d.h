
#ifndef CUB3D_H
#define CUB3D_H

typedef struct s_map
{
	char **grid;
	int width;
	int height;
	int player_x;
	int player_y;
	int player_count;
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
	int floor_color; // RGB int
	int ceil_color;
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

// close_game.c

// errors.c

#endif