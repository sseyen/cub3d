/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:06:45 by alisseye          #+#    #+#             */
/*   Updated: 2026/04/06 15:29:38 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move_to(t_map *map, double x, double y)
{
	int		cell_x;
	int		cell_y;
	char	cell;

	cell_x = (int)floor(x);
	cell_y = (int)floor(y);
	if (cell_y < 0 || cell_y >= map->height)
		return (0);
	if (cell_x < 0 || cell_x >= (int)ft_strlen(map->grid[cell_y]))
		return (0);
	cell = map->grid[cell_y][cell_x];
	if (cell == WALL || cell == SPACE)
		return (0);
	if (cell != FLOOR && cell != PLAYER_NORTH && cell != PLAYER_SOUTH
		&& cell != PLAYER_EAST && cell != PLAYER_WEST)
		return (0);
	return (1);
}

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
	if (can_move_to(map, new_x, p->pos_y))
		p->pos_x = new_x;
	if (can_move_to(map, p->pos_x, new_y))
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
	if (can_move_to(map, new_x, p->pos_y))
		p->pos_x = new_x;
	if (can_move_to(map, p->pos_x, new_y))
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
