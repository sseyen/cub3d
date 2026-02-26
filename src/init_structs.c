
#include "cub3d.h"

int	init_structs(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!game->mlx)
		return (error_msg("mlx_init failed at initialization"));
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		return (error_msg("mlx_new_image failed at initialization"));
	if (!mlx_image_to_window(game->mlx, game->img, 0, 0))
		return (error_msg("mlx_image_to_window failed at initialization"));
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (error_msg("malloc failed for map initialization"));
	ft_memset(game->map, 0, sizeof(t_map));
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return (error_msg("malloc failed for textures initialization"));
	ft_memset(game->textures, 0, sizeof(t_textures));
	game->player = NULL;
	game->buffer = NULL;
	return (1);
}
