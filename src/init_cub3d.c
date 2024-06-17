/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

void	ft_init_cub_vars(t_cub3d *cub3d)
{
	cub3d->map_len = 0;
	cub3d->map_width = 0;
	cub3d->map = NULL;
	cub3d->player_x = 0.0;
	cub3d->player_y = 0.0;
	cub3d->orientation = '\0';
	cub3d->vision_x = 0.0;
	cub3d->vision_y = 0.0;
	cub3d->fov_x = 0.0;
	cub3d->fov_y = 0.0;
	cub3d->mlx = NULL;
	cub3d->mlx_win = NULL;
	cub3d->keys.up = KEY_RELEASED;
	cub3d->keys.left = KEY_RELEASED;
	cub3d->keys.down = KEY_RELEASED;
	cub3d->keys.right = KEY_RELEASED;
	cub3d->keys.rot_left = KEY_RELEASED;
	cub3d->keys.rot_right = KEY_RELEASED;
	cub3d->keys.esc = KEY_RELEASED;
}

void	ft_init_texture_img(t_img *img)
{
	img->ptr = NULL;
	img->addr = NULL;
	img->size_line = 0;
	img->bpp = 0;
	img->height = 0;
	img->width = 0;
	img->endian = 0;
}

void	ft_init_structs(t_cub3d *cub3d)
{
	cub3d->texture->north = NULL;
	cub3d->texture->south = NULL;
	cub3d->texture->west = NULL;
	cub3d->texture->east = NULL;
	cub3d->texture->ceiling = 0;
	cub3d->texture->floor = 0;
	cub3d->texture->nbr_info = 0;
	ft_init_texture_img(&cub3d->screen);
	ft_init_texture_img(&cub3d->texture->img_no);
	ft_init_texture_img(&cub3d->texture->img_we);
	ft_init_texture_img(&cub3d->texture->img_so);
	ft_init_texture_img(&cub3d->texture->img_ea);
}

void	ft_init_cub3d(t_cub3d *cub3d)
{
	t_texture	*tmp;

	tmp = (t_texture *) malloc (sizeof(t_texture));
	if (!tmp)
		ft_safe_exit(cub3d, ERR_MEM_ALLOC);
	cub3d->texture = tmp;
	ft_init_structs(cub3d);
	ft_init_cub_vars(cub3d);
}
