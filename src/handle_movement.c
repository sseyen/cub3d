
#include "cub3d.h"

void	move_forward_back(t_player *p, t_map *map, int forward)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = MOVE_SPEED;
	if (!forward)
		speed = -MOVE_SPEED;
	new_x = p->pos_x + p->dir_x * speed;
	new_y = p->pos_y + p->dir_y * speed;
	if (map->grid[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (map->grid[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
}

void	move_side(t_player *p, t_map *map, int right)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = MOVE_SPEED;
	if (!right)
		speed = -MOVE_SPEED;
	new_x = p->pos_x + p->plane_x * speed;
	new_y = p->pos_y + p->plane_y * speed;
	if (map->grid[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (map->grid[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
}

void	rotate_player(t_player *p, int right)
{
	double	speed;
	double	old_dir_x;
	double	old_plane_x;

	speed = ROT_SPEED;
	if (!right)
		speed = -ROT_SPEED;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
	p->dir_y = old_dir_x * sin(speed) + p->dir_y * cos(speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
	p->plane_y = old_plane_x * sin(speed) + p->plane_y * cos(speed);
}

void	handle_movement(t_game *game)
{
	t_player	*p;
	t_map		*map;

	p = game->player;
	map = game->map;
	if (mlx_is_key_down(game->mlx, KEY_W))
		move_forward_back(p, map, 1);
	if (mlx_is_key_down(game->mlx, KEY_S))
		move_forward_back(p, map, 0);
	if (mlx_is_key_down(game->mlx, KEY_A))
		move_side(p, map, 0);
	if (mlx_is_key_down(game->mlx, KEY_D))
		move_side(p, map, 1);
	if (mlx_is_key_down(game->mlx, KEY_LEFT))
		rotate_player(p, 0);
	if (mlx_is_key_down(game->mlx, KEY_RIGHT))
		rotate_player(p, 1);
}
