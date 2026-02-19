
#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
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
		return (error_msg("Missing NO texture"));
	if (!game->textures->south_path)
		return (error_msg("Missing SO texture"));
	if (!game->textures->east_path)
		return (error_msg("Missing EA texture"));
	if (!game->textures->west_path)
		return (error_msg("Missing WE texture"));
	if (!game->textures->floor_color)
		return (error_msg("Missing F color"));
	if (!game->textures->ceil_color)
		return (error_msg("Missing C color"));
	return (1);
}

int	parse_header_line(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_texture(line + 3, &game->textures->north_path));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_texture(line + 3, &game->textures->south_path));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_texture(line + 3, &game->textures->west_path));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_texture(line + 3, &game->textures->east_path));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_color(line + 2, &game->textures->floor_color));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_color(line + 2, &game->textures->ceil_color));
	return (error_msg("Unknown identifier in header"));
}
