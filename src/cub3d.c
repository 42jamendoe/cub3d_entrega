/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

int	ft_check_arg(int argc, char **argv)
{
	size_t	pos;
	int		scene_fd;

	if (argc != CUB3D_ARGS)
	{
		printf("Error\nInvalid number of arguments\n");
		return (EXIT_FAILURE);
	}
	pos = ft_strlen(argv[ARG_SCENE_PATH]) - SCENE_CHAR_NBR;
	if (ft_strncmp(&argv[ARG_SCENE_PATH][(int)pos], ".cub", SCENE_CHAR_NBR))
	{
		printf("Error\nInvalid map extension\n");
		return (EXIT_FAILURE);
	}
	scene_fd = open(argv[ARG_SCENE_PATH], O_RDONLY);
	if (scene_fd < 1)
	{
		printf("%s", ERR_SCENE_FD);
		return (EXIT_FAILURE);
	}
	close(scene_fd);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (ft_check_arg(argc, argv))
		return (EXIT_FAILURE);
	cub3d = (t_cub3d *) malloc (sizeof(t_cub3d));
	if (!cub3d)
		return (EXIT_FAILURE);
	ft_init_cub3d(cub3d);
	ft_read_scene(cub3d, argv[ARG_SCENE_PATH]);
	ft_init_mlx(cub3d);
	mlx_loop_hook(cub3d->mlx, ft_run_window, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}
