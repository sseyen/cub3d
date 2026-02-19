
#include "cub3d.h"

// basically ft_strncmp but from the back
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

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n' || *line == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ; // for the het_nex_line not to skip to the end
		}
		if (is_map_line(line)) // starts with '1', '0', ' ', or player char
		{
			game->map->pending_line = line; // save for parse_map
			return (validate_header(game));
		}
		if (!parse_header_line(line, game))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (error_msg("Map section not found"));
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
	{
		close(fd);
		return (error_msg("Invalid map header"));
	}
	if (!parse_map(fd, game))
	{
		close(fd);
		return (error_msg("Invalid map"));
	}
	close(fd);
	return (1);
}
