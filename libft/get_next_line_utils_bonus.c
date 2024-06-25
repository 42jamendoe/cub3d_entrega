/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:25:44 by jamendoe          #+#    #+#             */
/*   Updated: 2022/12/09 18:26:18 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	else
		return (NULL);
}

int	ft_line_len(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		if (buffer[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

int	ft_line_break(char *buffer)
{
	int	line_break;

	if (!ft_strchr(buffer, '\n'))
		line_break = 0;
	else
		line_break = 1;
	return (line_break);
}
