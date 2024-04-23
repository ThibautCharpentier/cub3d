/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:12:34 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/01 16:12:34 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	add_start(t_win *win, int x, int y, int *start)
{
	*start = 1;
	win->map.startx = x;
	win->map.starty = y;
	win->map.direction = win->map.map[y][x];
}

static int	verify_start(char **map, t_win *win)
{
	int	x;
	int	y;
	int	start;

	start = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				if (!start)
					add_start(win, x, y, &start);
				map[y][x] = '0';
			}
		}
	}
	if (!start)
		return (0);
	return (1);
}

static int	check_around(char **map, int x, int y, t_win *win)
{
	if (y == 0)
		return (0);
	if (y == win->map.nbr_y - 1)
		return (0);
	if (x == 0)
		return (0);
	if (x == win->map.nbr_x - 1)
		return (0);
	if (map[y - 1][x - 1] == ' ' || map[y - 1][x] == ' '
		|| map[y - 1][x + 1] == ' ' || map[y][x - 1] == ' '
		|| map[y][x + 1] == ' ' || map[y + 1][x - 1] == ' '
		|| map[y + 1][x] == ' ' || map[y + 1][x + 1] == ' ')
		return (0);
	return (1);
}

static int	verify_closing(char **map, t_win *win)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if (!check_around(map, x, y, win))
					return (0);
			}
		}
	}
	return (1);
}

void	parsing_cub(char *arg, t_win *win)
{
	char	**file;
	int		i_file;
	int		x;
	int		y;

	file = check_file(arg, win);
	i_file = check_elements(file, win);
	check_map(file, i_file, win);
	free_tabstr(file);
	if (!win->map.map[0])
		print_error("Invalid map: map not found !\n", win);
	if (!verify_start(win->map.map, win))
		print_error("Invalid map: no starting point !\n", win);
	if (!verify_closing(win->map.map, win))
		print_error("Invalid map: map not closed !\n", win);
	y = -1;
	while (win->map.map[++y])
	{
		x = -1;
		while (win->map.map[y][++x])
		{
			if (win->map.map[y][x] == ' ')
				win->map.map[y][x] = '1';
		}
	}
}
