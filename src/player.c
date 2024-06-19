/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

void	ft_set_orientation(t_cub3d *cub3d)
{
	if (!cub3d->orientation)
		ft_safe_exit (cub3d, ERR_PLAYER_MISS);
	else if (cub3d->orientation == 'N' || cub3d->orientation == 'S')
	{
		cub3d->vision_x = 0;
		if (cub3d->orientation == 'N')
			cub3d->vision_y = -1;
		else
			cub3d->vision_y = 1;
	}
	else if (cub3d->orientation == 'E' || cub3d->orientation == 'W')
	{
		cub3d->vision_y = 0;
		if (cub3d->orientation == 'W')
			cub3d->vision_x = -1;
		else
			cub3d->vision_x = 1;
	}
	cub3d->fov_x = -cub3d->vision_y * FIELD_OF_VIEW;
	cub3d->fov_y = cub3d->vision_x * FIELD_OF_VIEW;
}

void	ft_load_player(t_cub3d *cub3d)
{
	int	i;
	int	n;

	n = 0;
	while (n < cub3d->map_len)
	{
		i = 0;
		while (i < cub3d->map_width)
		{
			if (cub3d->map[n][i] == 'N' || cub3d->map[n][i] == 'S' \
			|| cub3d->map[n][i] == 'W' || cub3d->map[n][i] == 'E')
			{
				cub3d->player_x = (double)i + 0.5;
				cub3d->player_y = (double)n + 0.5;
				cub3d->orientation = cub3d->map[n][i];
				break ;
			}
			i++;
			if (cub3d->map[n][i] == '\0')
				break ;
		}
		n++;
	}
	ft_set_orientation(cub3d);
}
