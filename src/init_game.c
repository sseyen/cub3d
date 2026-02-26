
#include "cub3d.h"

int	init_textures(t_game *game)
{
	game->textures->north_wall = mlx_load_png(game->textures->north_path);
	if (!game->textures->north_wall)
		return (error_msg("Failed to load north texture"));
	game->textures->south_wall = mlx_load_png(game->textures->south_path);
	if (!game->textures->south_wall)
		return (error_msg("Failed to load south texture"));
	game->textures->east_wall = mlx_load_png(game->textures->east_path);
	if (!game->textures->east_wall)
		return (error_msg("Failed to load east texture"));
	game->textures->west_wall = mlx_load_png(game->textures->west_path);
	if (!game->textures->west_wall)
		return (error_msg("Failed to load west texture"));
	return (1);
}

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
		return (error_msg("calloc failed for player loading"));
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
