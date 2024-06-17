/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

void	ft_move(t_cub3d *cub3d, double x, double y)
{
	if (x < 0)
	{
		if (cub3d->map[(int)(cub3d->player_y)][(int)(cub3d->player_x - \
		MARGIN + x * SPEED)] != '1')
			cub3d->player_x += (x * SPEED);
	}
	else
	{
		if (cub3d->map[(int)(cub3d->player_y)][(int)(cub3d->player_x + \
		MARGIN + x * SPEED)] != '1')
			cub3d->player_x += (x * SPEED);
	}
	if (y < 0)
	{
		if (cub3d->map[(int)(cub3d->player_y - MARGIN + y * \
		SPEED)][(int)(cub3d->player_x)] != '1')
			cub3d->player_y += (y * SPEED);
	}
	else
	{
		if (cub3d->map[(int)(cub3d->player_y + MARGIN + y * \
		SPEED)][(int)(cub3d->player_x)] != '1')
			cub3d->player_y += (y * SPEED);
	}
}

void	ft_rotate(t_cub3d *cub3d, int dir)
{
	double	vision;
	double	fieldofv;

	vision = cub3d->vision_x;
	cub3d->vision_x = vision * cos (dir * (double)ROTATION) - cub3d->vision_y * \
	sin(dir * (double)ROTATION);
	cub3d->vision_y = vision * sin (dir * (double)ROTATION) + cub3d->vision_y * \
	cos(dir * (double)ROTATION);
	fieldofv = cub3d->fov_x;
	cub3d->fov_x = fieldofv * cos (dir * (double)ROTATION) - cub3d->fov_y \
	* sin(dir * (double)ROTATION);
	cub3d->fov_y = fieldofv * sin (dir * (double)ROTATION) + cub3d->fov_y \
	* cos(dir * (double)ROTATION);
}

int	ft_press_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == UP)
		cub3d->keys.up = KEY_PRESSED;
	if (key_code == LEFT)
		cub3d->keys.left = KEY_PRESSED;
	if (key_code == DOWN)
		cub3d->keys.down = KEY_PRESSED;
	if (key_code == RIGHT)
		cub3d->keys.right = KEY_PRESSED;
	if (key_code == ROT_LEFT)
		cub3d->keys.rot_left = KEY_PRESSED;
	if (key_code == ROT_RIGHT)
		cub3d->keys.rot_right = KEY_PRESSED;
	if (key_code == ESCAPE)
		cub3d->keys.esc = KEY_PRESSED;
	return (0);
}

int	ft_release_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == UP)
		cub3d->keys.up = KEY_RELEASED;
	if (key_code == LEFT)
		cub3d->keys.left = KEY_RELEASED;
	if (key_code == DOWN)
		cub3d->keys.down = KEY_RELEASED;
	if (key_code == RIGHT)
		cub3d->keys.right = KEY_RELEASED;
	if (key_code == ROT_LEFT)
		cub3d->keys.rot_left = KEY_RELEASED;
	if (key_code == ROT_RIGHT)
		cub3d->keys.rot_right = KEY_RELEASED;
	if (key_code == ESCAPE)
		cub3d->keys.esc = KEY_RELEASED;
	return (0);
}

void	ft_check_move(t_cub3d *cub3d)
{
	if (cub3d->keys.up == KEY_PRESSED)
		ft_move(cub3d, cub3d->vision_x, cub3d->vision_y);
	if (cub3d->keys.down == KEY_PRESSED)
		ft_move(cub3d, -cub3d->vision_x, -cub3d->vision_y);
	if (cub3d->keys.left == KEY_PRESSED)
		ft_move(cub3d, cub3d->vision_y, -cub3d->vision_x);
	if (cub3d->keys.right == KEY_PRESSED)
		ft_move(cub3d, -cub3d->vision_y, cub3d->vision_x);
	if (cub3d->keys.rot_left == KEY_PRESSED)
		ft_rotate(cub3d, -1);
	if (cub3d->keys.rot_right == KEY_PRESSED)
		ft_rotate(cub3d, 1);
	if (cub3d->keys.esc == KEY_PRESSED)
		ft_close(cub3d);
}
