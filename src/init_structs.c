
#include "cub3d.h"

int	init_structs(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
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