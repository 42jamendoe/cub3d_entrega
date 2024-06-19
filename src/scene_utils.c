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

void	ft_clean_split(char **split)
{
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
}

void	ft_error_map_lines(t_cub3d *cub3d, char *line, int n_lin)
{
	free(line);
	if (n_lin > 0)
		ft_safe_exit (cub3d, ERR_MAP_SPACES);
}

void	ft_test_textures(t_cub3d *cub3d)
{
	int	fd;

	fd = open (cub3d->texture->north, O_RDWR);
	if (fd < 1)
		ft_safe_exit(cub3d, ERR_SCENE_TILE);
	close(fd);
	fd = open (cub3d->texture->south, O_RDWR);
	if (fd < 1)
		ft_safe_exit(cub3d, ERR_SCENE_TILE);
	close(fd);
	fd = open (cub3d->texture->east, O_RDWR);
	if (fd < 1)
		ft_safe_exit(cub3d, ERR_SCENE_TILE);
	close(fd);
	fd = open (cub3d->texture->west, O_RDWR);
	if (fd < 1)
		ft_safe_exit(cub3d, ERR_SCENE_TILE);
	close(fd);
}
