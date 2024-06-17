/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:00:10 by jamendoe          #+#    #+#             */
/*   Updated: 2023/03/14 21:00:14 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../includes/libft.h"

void	ft_check_spaces(t_cub3d *cub3d, int i, t_map_info ln)
{
	if (i == 0 && cub3d->map[ln.ln][i] == ' ')
	{
		if ((cub3d->map[ln.pl][i] != '1' && cub3d->map[ln.pl][i] != ' ') || \
		(cub3d->map[ln.ln][i + 1] != '1' && cub3d->map[ln.ln][i + 1] != ' ') || \
		(cub3d->map[ln.nl][i] != '1' && cub3d->map[ln.nl][i] != ' '))
			ft_safe_exit (cub3d, "ERR_WALLS");
	}
	else if ((i == ln.len_ln - 1) && cub3d->map[ln.ln][i] == ' ')
	{
		if ((cub3d->map[ln.pl][i] != '1' && cub3d->map[ln.pl][i] != ' ') || \
		(cub3d->map[ln.ln][i - 1] != '1' && cub3d->map[ln.ln][i - 1] != ' ') || \
		(cub3d->map[ln.nl][i] != '1' && cub3d->map[ln.nl][i] != ' '))
			ft_safe_exit (cub3d, "ERR_WALLS");
	}
	else if (cub3d->map[ln.ln][i] == ' ')
	{
		if ((cub3d->map[ln.pl][i] != '1' && cub3d->map[ln.pl][i] != ' ') || \
		(cub3d->map[ln.ln][i - 1] != '1' && cub3d->map[ln.ln][i - 1] != ' ') || \
		(cub3d->map[ln.ln][i + 1] != '1' && cub3d->map[ln.ln][i + 1] != ' ') || \
		(cub3d->map[ln.nl][i] != '1' && cub3d->map[ln.nl][i] != ' '))
			ft_safe_exit (cub3d, "ERR_WALLS");
	}
	else if ((i >= ln.len_pl && cub3d->map[ln.ln][i] != '1') || (i >= ln.len_nl \
	&& cub3d->map[ln.ln][i] != '1'))
		ft_safe_exit (cub3d, "ERR_WALLS");
}

void	ft_check_wall_ver(t_cub3d *cub3d, int j)
{
	int			i;
	t_map_info	ln;

	i = 0;
	ln.ln = j;
	ln.pl = j - 1;
	ln.nl = j + 1;
	ln.len_ln = (int)ft_strlen(cub3d->map[j]) - 1;
	ln.len_pl = (int)ft_strlen(cub3d->map[ln.pl]) - 1;
	ln.len_nl = (int)ft_strlen(cub3d->map[ln.nl]) - 1;
	while (i < ln.len_ln)
	{
		if (i > ln.len_pl)
			ln.pl = ln.ln;
		if (i > ln.len_nl)
			ln.nl = ln.ln;
		if ((i == 0 || i == ln.len_ln - 1) && (cub3d->map[j][i] != '1' \
		&& cub3d->map[j][i] != ' '))
			ft_safe_exit(cub3d, ERR_WALLS);
		else
			ft_check_spaces(cub3d, i, ln);
		i++;
	}
}

void	ft_check_wall_hor(t_cub3d *cub3d, int j)
{
	int	i;
	int	ln_adj;

	i = 0;
	while (i < (int)ft_strlen(cub3d->map[j]) - 2)
	{
		if (cub3d->map[j][i] != ' ' && cub3d->map[j][i] != '1')
			ft_safe_exit(cub3d, ERR_WALLS);
		if (cub3d->map[j][i] == ' ')
		{
			if (j == 0)
				ln_adj = 1;
			else
				ln_adj = cub3d->map_len - 2;
			if (i <= (int)ft_strlen (cub3d->map[ln_adj]) - 2)
			{
				if (cub3d->map[ln_adj][i] != ' ' && \
				cub3d->map[ln_adj][i] != '1')
					ft_safe_exit(cub3d, ERR_WALLS);
			}
		}
		i++;
	}
}

void	ft_check_chars(t_cub3d *cub3d)
{
	int	i;
	int	j;

	j = 0;
	while (j < cub3d->map_len)
	{
		i = 0;
		while (i < (int)ft_strlen(cub3d->map[j]) - 1)
		{
			if (!ft_strchr("NWSE10 ", cub3d->map[j][i]))
				ft_safe_exit(cub3d, ERR_CHAR_MAP);
			i++;
		}
		j++;
	}
}

void	ft_check_map(t_cub3d *cub3d)
{
	int	j;

	ft_check_chars(cub3d);
	j = 0;
	while (j < cub3d->map_len)
	{
		if (j == 0)
			ft_check_wall_hor(cub3d, j);
		else if (j < cub3d->map_len - 1)
			ft_check_wall_ver(cub3d, j);
		else if (j == cub3d->map_len - 1)
			ft_check_wall_hor(cub3d, cub3d->map_len - 1);
		j++;
	}
}
