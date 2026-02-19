
#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (*line == '\n' || *line == '\0')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	validate_header(t_game *game)
{
	if (!game->textures->north_path)
		return (error_msg("Missing NO texture in map header"));
	if (!game->textures->south_path)
		return (error_msg("Missing SO texture in map header"));
	if (!game->textures->east_path)
		return (error_msg("Missing EA texture in map header"));
	if (!game->textures->west_path)
		return (error_msg("Missing WE texture in map header"));
	if (!game->textures->floor_color)
		return (error_msg("Missing F color in map header"));
	if (!game->textures->ceil_color)
		return (error_msg("Missing C color in map header"));
	return (1);
}

// !! ft_strncmp is "other way arround", it has 0/1 swapped for true/flase
// that why we check !ft_strncmp()
int	parse_header_line(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_texture(line, &game->textures->north_path, 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_texture(line, &game->textures->south_path, 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_texture(line, &game->textures->west_path, 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_texture(line, &game->textures->east_path, 3));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_color(line, &game->textures->floor_color, 2, 0));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_color(line, &game->textures->ceil_color, 2, 0));
	return (error_msg("Unknown identifier in map header"));
}
