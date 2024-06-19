/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

int	ft_close(t_cub3d *cub3d)
{
	printf("%s", "THANK YOU FOR TEST");
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
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		ft_safe_exit (cub3d, "MLX_INIT_ERROR");
	cub3d->mlx_win = mlx_new_window(cub3d->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!cub3d->mlx_win)
		ft_safe_exit (cub3d, "MLX_INIT_ERROR");
	cub3d->screen.ptr = mlx_new_image(cub3d->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub3d->screen.ptr)
		ft_safe_exit (cub3d, "MLX_IMG_ERROR");
	cub3d->screen.addr = mlx_get_data_addr(cub3d->screen.ptr, \
	&cub3d->screen.bpp, &cub3d->screen.size_line, &cub3d->screen.endian);
	if (!cub3d->screen.addr)
		ft_safe_exit (cub3d, "MLX_ADDRR_ERROR");
	ft_load_textures(cub3d);
	mlx_hook(cub3d->mlx_win, 17, 0, ft_close, cub3d);
	mlx_hook(cub3d->mlx_win, 2, (1L << 0), ft_press_key, cub3d);
	mlx_hook(cub3d->mlx_win, 3, (1L << 1), ft_release_key, cub3d);
}
