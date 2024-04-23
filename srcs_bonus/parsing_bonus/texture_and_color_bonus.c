/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:50:38 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/03 16:50:38 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	atoi_cub_color(char *nptr)
{
	unsigned int	i;
	int				res;
	int				sign;

	res = 0;
	i = 0;
	sign = 0;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = 1;
		i++;
	}
	if (!ft_isdigit(nptr[i]))
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		if (res > 255)
			return (-1);
		i++;
	}
	if (res > 0 && sign == 1)
		return (-1);
	return (res);
}

static int	check_color(int *tab_color, int i_color, int *color)
{
	*color = ((tab_color[0] & 0x0ff) << 16 | (tab_color[1] & 0x0ff) << 8 \
		| (tab_color[2] & 0x0ff));
	if (i_color != 3 || tab_color[0] < 0 || tab_color[1] < 0
		|| tab_color[2] < 0)
	{
		free(tab_color);
		return (0);
	}
	free(tab_color);
	return (1);
}

static int	next_color(char *line, int i_line, int i_color)
{
	if (line[i_line] == '+' || line[i_line] == '-')
		i_line++;
	if (!ft_isdigit(line[i_line]))
		return (-1);
	while (line[i_line] && ft_isdigit(line[i_line]))
		i_line++;
	while (line[i_line] && ft_isspace(line[i_line]))
		i_line++;
	if (line[i_line] && line[i_line] != ',')
		return (-1);
	if (line[i_line] && i_color > 2)
		return (-1);
	if (!line[i_line])
		i_line--;
	return (i_line);
}

int	add_color(int *color, char *line, t_win *win, char **file)
{
	int	i_line;
	int	i_color;
	int	*tab_color;

	tab_color = malloc(sizeof(int) * 3);
	if (!tab_color)
	{
		free_tabstr(file);
		print_error_system("malloc", win);
	}
	i_line = -1;
	i_color = 0;
	while (line[++i_line] && i_color < 3)
	{
		if (ft_isspace(line[i_line]))
			continue ;
		if (!ft_isdigit(line[i_line]) && line[i_line] != '+'
			&& line[i_line] != '-')
			return (0);
		(tab_color)[i_color++] = atoi_cub_color(line + i_line);
		i_line = next_color(line, i_line, i_color);
		if (i_line == -1)
			return (0);
	}
	return (check_color(tab_color, i_color, color));
}

int	add_texture(int type, char *line, t_win *win, char **file)
{
	int		i_line;
	int		len;
	char	*str;

	i_line = -1;
	len = 0;
	str = NULL;
	while (line[++i_line])
	{
		if (ft_isspace(line[i_line]))
			continue ;
		if (str)
			return (0);
		while (line[i_line] && !ft_isspace(line[i_line]))
		{
			i_line++;
			len++;
		}
		str = strlcpy_malloc(line + i_line - len, len + 1, file, win);
		win->map.path[type] = str;
		i_line--;
	}
	if (!str)
		return (0);
	return (1);
}
