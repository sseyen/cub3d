
#include "cub3d.h"

void	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup_game(game);
	exit(0);
}