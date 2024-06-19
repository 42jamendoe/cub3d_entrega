/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

void	ft_clean_map(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->map_len)
	{
		if (cub3d->map[i])
			free(cub3d->map[i]);
		else
			break ;
		i++;
	}
	free(cub3d->map);
	cub3d->map = NULL;
}

void	ft_clean_images(t_cub3d *cub3d)
{
	if (cub3d->texture->img_no.ptr)
		mlx_destroy_image (cub3d->mlx, cub3d->texture->img_no.ptr);
	if (cub3d->texture->img_we.ptr)
		mlx_destroy_image (cub3d->mlx, cub3d->texture->img_we.ptr);
	if (cub3d->texture->img_so.ptr)
		mlx_destroy_image (cub3d->mlx, cub3d->texture->img_so.ptr);
	if (cub3d->texture->img_ea.ptr)
		mlx_destroy_image (cub3d->mlx, cub3d->texture->img_ea.ptr);
	if (cub3d->screen.ptr)
		mlx_destroy_image (cub3d->mlx, cub3d->screen.ptr);
	if (cub3d->mlx_win)
		mlx_destroy_window (cub3d->mlx, cub3d->mlx_win);
}

void	ft_clean_texture(t_cub3d *cub3d)
{
	if (cub3d->texture->north)
		free(cub3d->texture->north);
	if (cub3d->texture->south)
		free(cub3d->texture->south);
	if (cub3d->texture->west)
		free(cub3d->texture->west);
	if (cub3d->texture->east)
		free(cub3d->texture->east);
}

void	ft_close_fd(int min, int max)
{
	while (min < max)
	{
		close(min);
		min++;
	}
}

void	ft_safe_exit(t_cub3d *cub3d, char *msg)
{
	printf("%s", msg);
	ft_close_fd(0, 1024);
	ft_clean_images(cub3d);
	if (cub3d->mlx)
	{
		mlx_destroy_display (cub3d->mlx);
		free (cub3d->mlx);
	}
	if (cub3d->texture)
	{
		ft_clean_texture(cub3d);
		free(cub3d->texture);
		cub3d->texture = NULL;
	}
	if (cub3d->map)
		ft_clean_map(cub3d);
	free(cub3d);
	exit(EXIT_FAILURE);
}
