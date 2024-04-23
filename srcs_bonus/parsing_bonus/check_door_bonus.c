/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:25:47 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/23 19:25:47 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	check_around_door(char **map, int x, int y)
{
	if (map[y][x - 1] == '1')
	{
		if (map[y][x + 1] == '1')
			return (1);
	}
	if (map[y + 1][x] == '1')
	{
		if (map[y - 1][x] == '1')
			return (1);
	}
	return (0);
}

int	check_door(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '2')
				if (!check_around_door(map, x, y))
					return (0);
		}
	}
	return (1);
}
