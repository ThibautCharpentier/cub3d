/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:28:12 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/04 17:28:12 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	init_direction_two(t_map *map, t_ray *ray)
{
	if (map->direction == 'E')
	{
		ray->dirx = 1.0;
		ray->diry = 0.0;
		ray->planx = 0.0;
		ray->plany = 0.66;
	}
	else
	{
		ray->dirx = -1.0;
		ray->diry = 0.0;
		ray->planx = 0.0;
		ray->plany = -0.66;
	}
}

static void	init_direction(t_map *map, t_ray *ray)
{
	if (map->direction == 'N')
	{
		ray->dirx = 0.0;
		ray->diry = -1.0;
		ray->planx = 0.66;
		ray->plany = 0.0;
	}
	else if (map->direction == 'S')
	{
		ray->dirx = 0.0;
		ray->diry = 1.0;
		ray->planx = -0.66;
		ray->plany = 0.0;
	}
	else
		init_direction_two(map, ray);
}

void	init_raycasting(t_win *win, t_map *map, t_ray *ray)
{
	init_direction(map, ray);
	ray->posx = map->startx + 0.5;
	ray->posy = map->starty + 0.5;
	ray->door_x = 0;
	ray->door_y = 0;
	win->img_one.img = NULL;
	win->img_two.img = NULL;
	ray->mini.size = MAX_HEIGHT / 5;
	ray->mini.step = 8.0 / (double) ray->mini.size;
}
