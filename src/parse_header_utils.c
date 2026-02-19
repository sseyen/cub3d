
#include "cub3d.h"

int	parse_texture(char *line, char *texture_path, int i)
{
	char	*path;
	int		fd;

	while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		return (error_msg("Allocation failed"));
	i = ft_strlen(path) - 1;
	while (i >= 0 && (path[i] == ' ' || (path[i] >= '\t' && path[i] <= '\r')))
		path[i--] = '\0';
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(path), error_msg("Texture file not found"));
	close(fd);
	*texture_path = path;
	return (1);
}

int	parse_color(char *line, int **color, int i, int j)
{
	*color = (int *)malloc(3 * sizeof(int));
	if (!*color)
		return (error_msg("malloc failed for color codes"));
	while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		i++;
	while (line[i] && j <= 2 && (ft_isdigit(line[i]) || line[i] == ','))
	{
		if (line[i] == ',')
			return(free(*color), error_msg("Invalid color format"));
		(*color)[j] = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',')
		{
			i++;
			j++;
		}
	}
	if (j != 2 || (line[i] != '\0' && line[i] != '\n'))
		return (free(*color), error_msg("Invalid color format"));
	if ((*color)[0] < 0 || (*color)[0] > 255 
		|| (*color)[1] < 0 || (*color)[1] > 255
		|| (*color)[2] < 0 || (*color)[2] > 255)
		return (free(*color), error_msg("Invalid color format"));
	return (1);
}
