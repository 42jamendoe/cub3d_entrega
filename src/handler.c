/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

unsigned int	ft_texture_pixel(t_img *img, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(img->addr + (y * img->size_line) + \
	(x * img->bpp / 8));
	return (color);
}

unsigned int	ft_get_pixel(t_cub3d *cub3d, t_ray *ray)
{
	unsigned int	color;

	if (!ray->side)
	{
		if (cub3d->player_x > ray->map_x)
			color = ft_texture_pixel(&cub3d->texture->img_we, \
			ray->texture_x, ray->texture_y);
		else
			color = ft_texture_pixel(&cub3d->texture->img_ea, \
			ray->texture_x, ray->texture_y);
	}
	else
	{
		if (cub3d->player_y > ray->map_y)
			color = ft_texture_pixel(&cub3d->texture->img_no, \
			ray->texture_x, ray->texture_y);
		else
			color = ft_texture_pixel(&cub3d->texture->img_so, \
			ray->texture_x, ray->texture_y);
	}
	return (color);
}

void	ft_pixel_color(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	ft_color_img(t_cub3d *cub3d, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y <= ray->draw_start)
			ft_pixel_color(&cub3d->screen, x, y, cub3d->texture->ceiling);
		if (y >= ray->draw_start && y < ray->draw_end)
		{
			ray->texture_y = (int)ray->texture_position & (TEXTURE_HEIGHT - 1);
			ray->texture_position += ray->step;
			ft_pixel_color(&cub3d->screen, x, y, ft_get_pixel(cub3d, ray));
		}
		if (y >= ray->draw_end)
			ft_pixel_color(&cub3d->screen, x, y, cub3d->texture->floor);
		y++;
	}
}

int	ft_run_window(t_cub3d *cub3d)
{
	int		scr_line;
	t_ray	ray;

	scr_line = 0;
	ft_check_move(cub3d);
	while (scr_line < SCREEN_WIDTH)
	{
		ray.screen_column = 2 * ((double)scr_line / SCREEN_WIDTH) - 1;
		ray.ray_dir_x = cub3d->vision_x + cub3d->fov_x * ray.screen_column;
		ray.ray_dir_y = cub3d->vision_y + cub3d->fov_y * ray.screen_column;
		ray.map_x = (int)cub3d->player_x;
		ray.map_y = (int)cub3d->player_y;
		ft_get_deltas(cub3d, &ray);
		ft_find_initial_dist(cub3d, &ray);
		ft_hit_the_wall(cub3d, &ray);
		ft_perp_dist_wall(cub3d, &ray);
		ft_find_pixel_hit(cub3d, &ray);
		ft_color_img(cub3d, &ray, scr_line);
		scr_line++;
	}
	mlx_put_image_to_window (cub3d->mlx, cub3d->mlx_win, \
	cub3d->screen.ptr, 0, 0);
	return (0);
}
