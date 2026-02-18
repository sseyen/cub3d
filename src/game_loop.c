
int	game_loop(t_game *game)
{
	// This runs every frame automatically via mlx_loop_hook
	handle_movement(game); // update player based on keys
	raycasting_math(game); // calculate what to draw
	render_frame(game); // draw to screen
	mlx_put_image_to_window(game->mlx, game->win, ...);
	return (0);
}