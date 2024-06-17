/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

void	ft_find_pixel_hit(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_pixel = cub3d->player_y + ray->perp_dist * ray->ray_dir_y;
	else
		ray->wall_pixel = cub3d->player_x + ray->perp_dist * ray->ray_dir_x;
	ray->wall_pixel -= floor(ray->wall_pixel);
	ray->texture_x = (int)(ray->wall_pixel * (double)(TEXTURE_WIDTH));
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->texture_x = TEXTURE_WIDTH - ray->texture_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->texture_x = TEXTURE_WIDTH - ray->texture_x - 1;
	ray->step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	ray->texture_position = (ray->draw_start - SCREEN_HEIGHT / 2 \
	+ ray->line_height / 2) * ray->step;
}

void	ft_perp_dist_wall(t_cub3d *cub3d, t_ray *ray)
{
	(void )cub3d;
	if (ray->side == 0)
		ray->perp_dist = (ray->side_x - ray->delta_x);
	else
		ray->perp_dist = (ray->side_y - ray->delta_y);
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_dist);
	ray->draw_start = -(ray->line_height / 2) + (SCREEN_HEIGHT / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (SCREEN_HEIGHT / 2);
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	ft_hit_the_wall(t_cub3d *cub3d, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub3d->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	ft_find_initial_dist(t_cub3d *cub3d, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (cub3d->player_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - cub3d->player_x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (cub3d->player_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - cub3d->player_y) * ray->delta_y;
	}
	ray->hit = 0;
}

void	ft_get_deltas(t_cub3d *cub3d, t_ray *ray)
{
	(void) cub3d;
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->ray_dir_y);
}
