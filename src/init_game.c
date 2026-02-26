
#include "cub3d.h"

int	set_direction(t_player *player, char spawn)
{
	if (spawn == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (spawn == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (spawn == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (spawn == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	else
		return (0);
	return (1);
}

int	init_player(t_game *game)
{
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		return (error_msg("malloc failed for player initialization"));
	game->player->pos_x = game->map->player_x + 0.5;
	game->player->pos_y = game->map->player_y + 0.5;
	if (!set_direction(game->player,
		game->map->grid[game->map->player_y][game->map->player_x]))
		return (error_msg("player direction has to be 'N', 'S', 'E' or 'W'"))
	return (1);
}

int init_game(t_game *game)
{
	if (!init_textures(game))	// mlx_load_png each path → store in textures struct
		return (0);
	if (!init_player(game))		// set pos/dir/plane from player_x/y + spawn char
		return (0);
	return (1);
}
