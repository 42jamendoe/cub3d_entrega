/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

void	ft_exit_cub_error(t_cub3d *cub3d)
{
	if (cub3d->error_nbr == CUB_SCENE_INFO)
		ft_safe_exit(cub3d, ERR_SCENE_INFO);
	else if (cub3d->error_nbr == CUB_FORMAT_RGB)
		ft_safe_exit(cub3d, ERR_SCENE_COLOR);
	else if (cub3d->error_nbr == CUB_RGB_VALUE)
		ft_safe_exit(cub3d, ERR_RGB_VALUE);
	else if (cub3d->error_nbr == CUB_MAP_INFO)
		ft_safe_exit(cub3d, ERR_MAP_SPACES);
	else
		ft_safe_exit(cub3d, ERR_CUB_REVIEW);
}

void	ft_assign_color(t_cub3d *cub3d, unsigned int *c, char l)
{
	unsigned int	rgb;

	rgb = 0;
	if (cub3d->error_nbr > 0 || c[0] > 255 || c[1] > 255 || c[2] > 255)
		cub3d->error_nbr = CUB_RGB_VALUE;
	if (cub3d->error_nbr == CUB_NO_ERRORS)
		rgb = c[0] << 16 | c[1] << 8 | c[2];
	if (l == 'C')
	{
		cub3d->texture->has_c = 1;
		cub3d->texture->ceiling = rgb;
	}
	if (l == 'F')
	{
		cub3d->texture->has_f = 1;
		cub3d->texture->floor = rgb;
	}
}

int	ft_repeat_texture_info(t_cub3d *cub3d, char *line)
{
	if ((line[0] == 'N' && line[1] == 'O' && cub3d->texture->north) || \
		(line[0] == 'S' && line[1] == 'O' && cub3d->texture->south) || \
		(line[0] == 'W' && line[1] == 'E' && cub3d->texture->west) || \
		(line[0] == 'E' && line[1] == 'A' && cub3d->texture->east))
		return (1);
	return (0);
}

void	ft_clean_split(char **split)
{
	if (split && split[0] && split[1] && split[2])
		free(split[2]);
	if (split && split[0] && split[1])
		free(split[1]);
	if (split && split[0])
		free(split[0]);
	if (split)
		free(split);
}

void	ft_error_map_lines(t_cub3d *cub3d, char *line, int n_lin)
{
	free(line);
	if (n_lin > 0)
		cub3d->error_nbr = CUB_MAP_INFO;
}
