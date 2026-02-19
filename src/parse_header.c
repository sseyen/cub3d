
#include "cub3d.h"

// the while loop after len removes any trailing whitespace chars such as \n
// at the end just opening and closing fd to check if file exists
int	parse_texture(char *line, char **texture_path, int i)
{
	int	fd;
	int	len;

	if (*texture_path)
		return (error_msg("Duplicate texture in map header"));
	while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		i++;
	*texture_path = ft_strdup(line + i);
	if (!*texture_path)
		return (error_msg("ft_strdup failed for texture path"));
	len = ft_strlen(*texture_path) - 1;
	while (len >= 0 && ((*texture_path)[len] == ' ' 
	|| ((*texture_path)[len] >= '\t' && (*texture_path)[len] <= '\r')))
		(*texture_path)[len--] = '\0';
	if (!correct_extension(*texture_path, ".xpm", 4))
		return (free(*texture_path), error_msg("Texture must be a .xpm file"));
	fd = open(*texture_path, O_RDONLY);
	if (fd < 0)
		return (free(*texture_path), error_msg("Texture file not found"));
	close(fd);
	return (1);
}

// looks complicated, but its cuz of the spaces and comas
int	valid_color_input(char *line, int **color, int i, int j)
{
	while (line[i] && j < 3
		&& ((line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		|| ft_isdigit(line[i]) || line[i] == ','))
	{
		if (line[i] == ',')
			return (free(*color), *color = NULL,
				error_msg("Invalid color format"));
		while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
			i++;
		(*color)[j] = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
			i++;
		if (line[i] == ',')
		{
			i++;
			j++;
		}
		while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
			i++;
	}
	if (j != 3 || (line[i] != '\0' && line[i] != '\n'))
		return (free(*color), *color = NULL, error_msg("Invalid color format"));
	return (1);
}

int	parse_color(char *line, int **color, int i)
{
	int j;

	j = 0;
	if (*color)
		return (error_msg("Duplicate color in map header"));
	while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		i++;
	*color = (int *)malloc(3 * sizeof(int));
	if (!*color)
		return (error_msg("malloc failed for color codes"));
	if (!valid_color_input(line, color, i, j))
		return (0);
	if ((*color)[0] < 0 || (*color)[0] > 255
		|| (*color)[1] < 0 || (*color)[1] > 255
		|| (*color)[2] < 0 || (*color)[2] > 255)
		return (free(*color), *color = NULL, error_msg("Invalid color format"));
	return (1);
}

int	is_map_line(char *line)
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
		return (parse_color(line, &game->textures->floor_color, 2));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_color(line, &game->textures->ceil_color, 2));
	return (error_msg("Unknown identifier in map header"));
}
