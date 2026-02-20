
#include "cub3d.h"

int	only_map_chars(char *line)
{
	int	i;
	int	has_content;

	i = 0;
	has_content = 0;
	if (*line == '\n' || *line == '\0')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		if (line[i] != ' ')
			has_content = 1;
		i++;
	}
	return (has_content);
}

// basically ft_strncmp but from the back
int	correct_extension(char *path, char *ext, int ext_len)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i <= ext_len)
		return (0);
	i--;
	ext_len--;
	while (ext_len >= 0)
	{
		if (path[i] != ext[ext_len])
			return (0);
		i--;
		ext_len--;
	}
	return (1);
}

int	parse_header(int fd, t_game *game)
{
	char	*line;

	line = mini_gnl(fd);
	while (line != NULL)
	{
		if (*line == '\n' || *line == '\0')
		{
			free(line);
			line = mini_gnl(fd);
			continue ; // for the het_nex_line not to skip to the end
		}
		if (only_map_chars(line))
		{
			game->map->pending_line = line; // save for parse_map
			return (validate_header(game));
		}
		if (!parse_header_line(line, game)) // save current data and move to next
		{
			game->map->pending_line = line; // hand off to cleanup_game
			return (0);
		}
		free(line);
		line = mini_gnl(fd);
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

	if (!correct_extension(path, ".cub", 4)) // .cub is always 4 chars
		return (error_msg("Invalid map file type"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Could not open map file"));
	if (!parse_header(fd, game))
		return (close(fd), cleanup_game(game), 0);
	if (!parse_map(fd, game))
		return (close(fd), cleanup_game(game), 0);
	close(fd);
	return (1);
}
