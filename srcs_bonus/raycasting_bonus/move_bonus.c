/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:13:53 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/15 18:13:53 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	move_up(t_ray *ray, t_key *key, char **map)
{
	int		x;
	int		y;
	char	mapx;
	char	mapy;

	if (ray->dirx >= 0)
		x = 1;
	else
		x = -1;
	if (ray->diry >= 0)
		y = 1;
	else
		y = -1;
	mapx = map[(int)ray->posy][(int)(ray->posx + (x * key->movespeed * 10))];
	mapy = map[(int)(ray->posy + (y * key->movespeed * 10))][(int)ray->posx];
	if (mapx == '0' || mapx == '4')
		ray->posx += ray->dirx * key->movespeed;
	if (mapy == '0' || mapy == '4')
		ray->posy += ray->diry * key->movespeed;
	return (1);
}

static int	move_down(t_ray *ray, t_key *key, char **map)
{
	int		x;
	int		y;
	char	mapx;
	char	mapy;

	if (ray->dirx >= 0)
		x = 1;
	else
		x = -1;
	if (ray->diry >= 0)
		y = 1;
	else
		y = -1;
	mapx = map[(int)ray->posy][(int)(ray->posx - (x * key->movespeed * 10))];
	mapy = map[(int)(ray->posy - (y * key->movespeed * 10))][(int)ray->posx];
	if (mapx == '0' || mapx == '4')
		ray->posx -= ray->dirx * key->movespeed;
	if (mapy == '0' || mapy == '4')
		ray->posy -= ray->diry * key->movespeed;
	return (1);
}

static int	move_left(t_ray *ray, t_key *key, char **map)
{
	int		x;
	int		y;
	char	mapx;
	char	mapy;

	if (ray->dirx >= 0)
		x = 1;
	else
		x = -1;
	if (ray->diry >= 0)
		y = 1;
	else
		y = -1;
	mapx = map[(int)ray->posy][(int)(ray->posx + (y * key->movespeed * 10))];
	mapy = map[(int)(ray->posy - (x * key->movespeed * 10))][(int)ray->posx];
	if (mapx == '0' || mapx == '4')
		ray->posx += ray->diry * key->movespeed;
	if (mapy == '0' || mapy == '4')
		ray->posy -= ray->dirx * key->movespeed;
	return (1);
}

static int	move_right(t_ray *ray, t_key *key, char **map)
{
	int		x;
	int		y;
	char	mapx;
	char	mapy;

	if (ray->dirx >= 0)
		x = 1;
	else
		x = -1;
	if (ray->diry >= 0)
		y = 1;
	else
		y = -1;
	mapx = map[(int)ray->posy][(int)(ray->posx - (y * key->movespeed * 10))];
	mapy = map[(int)(ray->posy + (x * key->movespeed * 10))][(int)ray->posx];
	if (mapx == '0' || mapx == '4')
		ray->posx -= ray->diry * key->movespeed;
	if (mapy == '0' || mapy == '4')
		ray->posy += ray->dirx * key->movespeed;
	return (1);
}

void	move(t_ray *ray, t_key *key, char **map)
{
	if (key->up)
		move_up(ray, key, map);
	if (key->down)
		move_down(ray, key, map);
	if (key->left)
		move_left(ray, key, map);
	if (key->right)
		move_right(ray, key, map);
}
