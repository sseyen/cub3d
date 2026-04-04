#include "cub3d.h"

void	get_ray_direction(t_ray *ray, t_player *p, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->ray_dir_x = p->dir_x + p->plane_x * camera_x;
	ray->ray_dir_y = p->dir_y + p->plane_y * camera_x;
	ray->map_x = (int)floor(p->pos_x);
	ray->map_y = (int)floor(p->pos_y);
	ray->hit = 0;
	ray->side = 0;
}

void	calc_step_distance(t_ray *ray, t_player *p)
{
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

void	find_nearest_wall(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= map->height)
			break ;
		if (ray->map_x < 0
			|| ray->map_x >= (int)ft_strlen(map->grid[ray->map_y]))
			break ;
		if (map->grid[ray->map_y][ray->map_x] == '1'
			|| map->grid[ray->map_y][ray->map_x] == ' ')
			ray->hit = 1;
	}
}

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	raycasting_math(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		get_ray_direction(&ray, game->player, x);
		calc_step_distance(&ray, game->player);
		find_nearest_wall(&ray, game->map);
		calc_wall_height(&ray);
		draw_column(game, &ray, x);
		x++;
	}
}
