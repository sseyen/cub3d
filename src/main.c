
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg("Usage: ./cub3D <map.cub>"));
	if (!init_structs(&game)) // allocate/zero map and textures
		return (error_msg("Init failed"));
	if (!parse_file(argv[1], &game)) // parsing + validation
		return (error_msg("Invalid map file"));
	if (!init_game(&game))
		return (error_exit("Game init failed"));
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_press, &game); // keyboard hadling
	mlx_hook(game.win, DestroyNotify, 0, &close_game, &game); // window closer
	mlx_loop_hook(game.mlx, &game_loop, &game); // set function adress
	mlx_loop(game.mlx); // run loop infinitely
	
	cleanup_game(&game);
	return (0);
}
