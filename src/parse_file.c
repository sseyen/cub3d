
#include "cub3d.h"

int	check_extension(char *path, char *ext, int ext_len)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i <= ext_len)
		return (1);
	while (ext_len >= 0)
	{
		if (path[i] != ext[ext_len])
			return (1);
		i--;
		ext_len--;
	}
	return (0);
}

int	parse_header(int fd, t_game *game)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (*line == '\n' || *line == '\0') // skip empty lines
		{ 
			free(line); 
			continue ; 
		}
		if (is_map_line(line)) // hit the map, stop
			return (free(line), 1);
		if (!parse_header_line(line, game)) // NO/SO/WE/EA/F/C
			return (free(line), 0);
		free(line);
	}
	return (validate_header(game)); // all 6 required info present?
}

int	parse_map(int fd, t_game *game)
{
	if (!collect_map_lines(fd, game))
		return (0);
	if (!validate_map_chars(game))
		return (error_msg("Invalid character in map"));
	if (game->map->player_count != 1)
		return (error_msg("Map must have exactly one player"));
	if (!validate_map_closed(game))
		return (error_msg("Map is not closed"));
	return (1);
}

int	parse_file(char *path, t_game *game)
{
	int		fd;

	if (!check_extension(path, ".cub", 4)) // .cub is always 4 chars
		return (error_msg("Invalid map file type"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Could not open map file"));
	if (!parse_header(fd, game))
		return (close(fd), 0);
	if (!parse_map(fd, game))
		return (close(fd), 0);
	close(fd);
	return (1);
}
