
#include "cub3d.h"

int	error_msg(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (0);
}