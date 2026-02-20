
#include "cub3d.h"

int	append_line(t_map *map, char *line)
{
	char	**new_grid;
	int		i;
	int		len;

	new_grid = malloc((map->height + 2) * sizeof(char *));
	if (!new_grid)
		return (0);
	i = -1;
	while (++i < map->height)
		new_grid[i] = map->grid[i];
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_grid[map->height] = ft_strdup(line);
	new_grid[map->height + 1] = NULL;
	free(map->grid);
	map->grid = new_grid;
	map->height++;
	if (new_grid[map->height - 1] != NULL)
		return (1);
	return (0);
}

int	collect_map_lines(int fd, t_game *game)
{
	game->map->grid = malloc(sizeof(char *));
	if (!game->map->grid)
		return (0);
	game->map->grid[0] = NULL;
	while (game->map->pending_line != NULL)
	{
		if (!append_line(game->map, game->map->pending_line))
		{
			free(game->map->pending_line);
			game->map->pending_line = NULL;
			return (0);
		}		
		free(game->map->pending_line);
		game->map->pending_line = get_next_line(fd);
	}
	return (1);
}

int	validate_map_chars(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (game->map->grid[y][++x])
		{
			c = game->map->grid[y][x];
			if (c != '1' && c != '0' && c != ' '
				&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
				return (0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->map->player_x = x;
				game->map->player_y = y;
				game->map->player_count++;
			}
		}
		if (x > game->map->width)
			game->map->width = x;
	}
	return (1);
}

int	is_open(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(map->grid[y]))
		return (1);
	if (map->grid[y][x] == ' ')
		return (1);
	return (0);
}

int	validate_map_closed(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			c = game->map->grid[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				if (is_open(game->map, y - 1, x) || is_open(game->map, y + 1, x)
					|| is_open(game->map, y, x - 1) 
					|| is_open(game->map, y, x + 1))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}
