
#include "cub3d.h"

int	init_structs(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->player = NULL;
	game->buffer = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (error_msg("malloc failed for map"));
	ft_memset(game->map, 0, sizeof(t_map));
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return (free(game->map), game->map = NULL, error_msg("malloc failed for textures"));
	ft_memset(game->textures, 0, sizeof(t_textures));
	return (1);
}