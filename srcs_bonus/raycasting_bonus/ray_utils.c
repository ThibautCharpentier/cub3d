/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:56:55 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/24 12:56:55 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	is_hit(char c)
{
	if (c == '1')
		return (1);
	else if (c == '2')
		return (2);
	return (0);
}

void	position_player_at_door(t_ray *ray, char **map)
{
	int	x;
	int	y;

	x = (int) ray->posx;
	y = (int) ray->posy;
	if (map[ray->door_y][ray->door_x] == '4')
	{
		if (!(x == ray->door_x && y == ray->door_y)
			&& !(x == ray->door_x && y == ray->door_y + 1)
			&& !(x == ray->door_x && y == ray->door_y - 1)
			&& !(x == ray->door_x + 1 && y == ray->door_y)
			&& !(x == ray->door_x - 1 && y == ray->door_y)
			&& !(x == ray->door_x - 1 && y == ray->door_y - 1)
			&& !(x == ray->door_x - 1 && y == ray->door_y + 1)
			&& !(x == ray->door_x + 1 && y == ray->door_y - 1)
			&& !(x == ray->door_x + 1 && y == ray->door_y + 1))
			map[ray->door_y][ray->door_x] = '2';
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int	*dst;

	dst = img->addr + (y * img->line_length / 4 + x);
	*(unsigned int *) dst = color;
}
