
#include "cub3d.h"

int init_game(t_game *game)
{
	if (!init_textures(game))   // mlx_load_png each path → store in textures struct
		return (0);
	if (!init_player(game))     // set pos/dir/plane from player_x/y + spawn char
		return (0);
	mlx_loop_hook(game->mlx, &game_loop, game);  // register frame callback
	mlx_close_hook(game->mlx, &close_game, game); // ESC / window close
	return (1);
}
