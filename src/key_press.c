
#include "cub3d.h"

void	key_press(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == KEY_ESC && keydata.action == MLX_PRESS)
		close_game(param);
}
