/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

int	ft_define_color(t_cub3d *cub3d, char *line, char letter)
{
	char			**split;
	unsigned int	color[3];
	unsigned int	rgb;

	line++;
	while (line[0] == ' ' || line [0] == '\t')
		line++;
	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		ft_safe_exit (cub3d, ERR_SCENE_COLOR);
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	if (color [0] > 255 || color [1] > 255 \
	|| color [2] > 255)
		ft_safe_exit (cub3d, ERR_RGB_VALUE);
	rgb = color[0] << 16 | color[1] << 8 | color[2];
	if (letter == 'C')
		cub3d->texture->ceiling = rgb;
	if (letter == 'F')
		cub3d->texture->floor = rgb;
	return (EXIT_SUCCESS);
}

void	ft_build_map(t_cub3d *cub3d, char *line, int *n_lin)
{
	if ((line[0] == 'N' && line[1] == 'O') || \
	(line[0] == 'S' && line[1] == 'O') || \
	(line[0] == 'W' && line[1] == 'E') || \
	(line[0] == 'E' && line[1] == 'A') || \
	(line[0] == 'F' || line[0] == 'C'))
	{
		cub3d->texture->nbr_info++;
		if (cub3d->texture->nbr_info > 6)
			ft_safe_exit(cub3d, ERR_SCENE_INFO);
		ft_test_textures(cub3d);
	}
	else if (line[0] == '0' || line[0] == '1' || line[0] == 'N' \
	|| line[0] == 'S' || line[0] == 'W' || line[0] == 'E' \
	|| line[0] == ' ' || line[0] == '\t')
	{
		cub3d->map[(*n_lin)] = line;
		(*n_lin)++;
	}
}

void	ft_identify_line(t_cub3d *cub3d, char *line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line[0] == 'N' && line[1] == 'O')
		cub3d->texture->north = ft_substr(line, 3, line_len - 4);
	else if (line[0] == 'S' && line[1] == 'O')
		cub3d->texture->south = ft_substr(line, 3, line_len - 4);
	else if (line[0] == 'W' && line[1] == 'E')
		cub3d->texture->west = ft_substr(line, 3, line_len - 4);
	else if (line[0] == 'E' && line[1] == 'A')
		cub3d->texture->east = ft_substr(line, 3, line_len - 4);
	else if (line[0] == 'F' || line[0] == 'C')
		ft_define_color(cub3d, line, line[0]);
	else if (line[0] == '0' || line[0] == '1' || line[0] == 'N' || \
	line[0] == 'S' || line[0] == 'W' || line[0] == 'E' || \
	line[0] == ' ' || line[0] == '\t')
	{
		cub3d->map_len++;
		if ((int)line_len > cub3d->map_width)
			cub3d->map_width = (int)line_len;
	}
	free(line);
}

int	ft_info_textures(t_cub3d *cub3d, char *scene, int stage)
{
	char	*line;
	int		scene_fd;
	int		n_lin;

	scene_fd = open(scene, O_RDONLY);
	if (scene_fd < 0)
		return (EXIT_FAILURE);
	n_lin = 0;
	while (1)
	{
		line = get_next_line(scene_fd);
		if (!line)
			break ;
		if (line[0] != '\n')
		{
			if (stage == READ_TEXTURES)
				ft_identify_line(cub3d, line);
			else
				ft_build_map(cub3d, line, &n_lin);
		}
		else
			ft_error_map_lines(cub3d, line, n_lin);
	}
	close(scene_fd);
	return (EXIT_SUCCESS);
}

int	ft_read_scene(t_cub3d *cub3d, char *argv)
{
	char	**tmp;

	if (ft_info_textures(cub3d, argv, READ_TEXTURES))
		ft_safe_exit(cub3d, ERR_SCENE_FD);
	if (cub3d->map_len == 0)
		ft_safe_exit(cub3d, ERR_SCENE_FIX);
	tmp = (char **) malloc (cub3d->map_len * sizeof(char *));
	if (!tmp)
		ft_safe_exit(cub3d, ERR_MEM_ALLOC);
	cub3d->map = tmp;
	ft_info_textures(cub3d, argv, WRITE_TEXTURES);
	ft_load_player(cub3d);
	ft_check_map(cub3d);
	return (EXIT_SUCCESS);
}
