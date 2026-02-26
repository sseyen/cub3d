
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg("Usage: ./cub3D <map.cub>"));
	if (!init_structs(&game)) // allocate/zero map and textures
		return (cleanup_game(&game), error_msg("Init failed"));
	if (!parse_file(argv[1], &game)) // parsing + validation
		return (cleanup_game(&game), error_msg("Invalid map file"));
	if (!init_game(&game)) // put init and parse together
		return (cleanup_game(&game), error_msg("Game init failed"));

	mlx_loop_hook(game.mlx, &game_loop, &game); // register frame callback
	mlx_close_hook(game.mlx, &close_game, &game); // ESC/window X button
	mlx_key_hook(game.mlx, &key_press, &game); // keyboard events
	
	mlx_loop(game.mlx);

	cleanup_game(&game);
	return (0);
}
