
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
	if (textures->north_wall)
		mlx_delete_texture(textures->north_wall);
	if (textures->south_wall)
		mlx_delete_texture(textures->south_wall);
	if (textures->east_wall)
		mlx_delete_texture(textures->east_wall);
	if (textures->west_wall)
		mlx_delete_texture(textures->west_wall);
	if (textures->floor_color)
		free(textures->floor_color);
	if (textures->ceil_color)
		free(textures->ceil_color);
	free(textures);
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
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_textures(game->textures);
	cleanup_map(game->map);
	if (game->player)
		free(game->player);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup_game(game);
	exit(0);
}
