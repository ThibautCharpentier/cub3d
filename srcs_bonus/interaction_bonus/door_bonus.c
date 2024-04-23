/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:44:24 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/23 17:44:24 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static char	find_direction(t_win *win)
{
	double	dirx;
	double	diry;

	dirx = win->ray.dirx;
	diry = win->ray.diry;
	if (dirx < 0)
		dirx = dirx * -1;
	if (diry < 0)
		diry = diry * -1;
	if (dirx > diry)
	{
		if (win->ray.dirx < 0)
			return ('W');
		else
			return ('E');
	}
	else
	{
		if (win->ray.diry < 0)
			return ('N');
		else
			return ('S');
	}
}

static int	is_different_door(t_win *win, int y, int x)
{
	if (win->map.map[win->ray.door_y][win->ray.door_x] == '4'
			&& !(win->ray.door_y == 0 && win->ray.door_x == 0)
			&& !(win->ray.door_y == y && win->ray.door_x == x))
		return (1);
	return (0);
}

void	open_door(t_win *win)
{
	char	direction;
	int		x;
	int		y;

	x = (int) win->ray.posx;
	y = (int) win->ray.posy;
	direction = find_direction(win);
	if (direction == 'N')
		y -= 1;
	else if (direction == 'S')
		y += 1;
	else if (direction == 'W')
		x -= 1;
	else if (direction == 'E')
		x += 1;
	if (win->map.map[y][x] == '2')
	{
		win->map.map[y][x] = '4';
		if (is_different_door(win, y, x))
			win->map.map[win->ray.door_y][win->ray.door_x] = '2';
		win->ray.door_x = x;
		win->ray.door_y = y;
	}
	else if (win->map.map[y][x] == '4')
		win->map.map[y][x] = '2';
}
