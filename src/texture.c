/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:07:43 by alisseye          #+#    #+#             */
/*   Updated: 2026/04/04 12:07:44 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (game->textures->east_wall);
		return (game->textures->west_wall);
	}
	if (ray->ray_dir_y > 0)
		return (game->textures->south_wall);
	return (game->textures->north_wall);
}

uint32_t	get_tex_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	int		idx;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	idx = (tex_y * (int)tex->width + tex_x) * (int)tex->bytes_per_pixel;
	r = tex->pixels[idx];
	g = tex->pixels[idx + 1];
	b = tex->pixels[idx + 2];
	return ((uint32_t)(r << 24) | (g << 16) | (b << 8) | tex->pixels[idx + 3]);
}

uint32_t	rgb_to_color(int *rgb)
{
	return ((uint32_t)(rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}
