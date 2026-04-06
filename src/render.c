/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:07:37 by alisseye          #+#    #+#             */
/*   Updated: 2026/04/04 12:07:38 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *game, t_ray *ray, int x)
{
	uint32_t	color;
	int			y;

	color = rgb_to_color(game->textures->ceil_color);
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

void	draw_floor(t_game *game, t_ray *ray, int x)
{
	uint32_t	color;
	int			y;

	color = rgb_to_color(game->textures->floor_color);
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

int	get_tex_offset(t_ray *ray, t_player *p)
{
	int	tex_x;

	if (ray->side == 0)
		ray->wall_x = p->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = p->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex_x = (int)(ray->wall_x * (double)TILE_SIZE);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex_x - 1;
	if (ray->side == 0 && ray->ray_dir_x < 0)
		tex_x = TILE_SIZE - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		tex_x = TILE_SIZE - tex_x - 1;
	return (tex_x);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	mlx_texture_t	*tex;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				y;

	tex = get_wall_texture(game, ray);
	tex_x = get_tex_offset(ray, game->player);
	step = (double)TILE_SIZE / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2.0
			+ ray->line_height / 2.0) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		mlx_put_pixel(game->img, x, y,
			get_tex_color(tex, tex_x, (int)tex_pos & (TILE_SIZE - 1)));
		tex_pos += step;
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	draw_ceiling(game, ray, x);
	draw_wall(game, ray, x);
	draw_floor(game, ray, x);
}
