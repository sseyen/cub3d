
#include "cub3d.h"

void	cleanup_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->north_path)
		free(textures->north_path);
	if (textures->south_path)
		free(textures->south_path);
	if (textures->east_path)
		free(textures->east_path);
	if (textures->west_path)
		free(textures->west_path);
	if (textures->floor_color)
		free(textures->floor_color);
	if (textures->ceil_color)
		free(textures->ceil_color);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	if (map->pending_line)
		free(map->pending_line);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_textures(game->textures);
	cleanup_map(game->map);
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}