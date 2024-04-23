/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:52:27 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/15 19:52:27 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	rotate_right(t_ray *ray, t_key *key, double dir, double plan)
{
	ray->dirx = dir * cos(key->rotspeed) - ray->diry * sin(key->rotspeed);
	ray->diry = dir * sin(key->rotspeed) + ray->diry * cos(key->rotspeed);
	ray->planx = plan * cos(key->rotspeed)
		- ray->plany * sin(key->rotspeed);
	ray->plany = plan * sin(key->rotspeed) + ray->plany * cos(key->rotspeed);
}

static void	rotate_left(t_ray *ray, t_key *key, double dir, double plan)
{
	ray->dirx = dir * cos(-key->rotspeed) - ray->diry * sin(-key->rotspeed);
	ray->diry = dir * sin(-key->rotspeed) + ray->diry * cos(-key->rotspeed);
	ray->planx = plan * cos(-key->rotspeed)
		- ray->plany * sin(-key->rotspeed);
	ray->plany = plan * sin(-key->rotspeed) + ray->plany * cos(-key->rotspeed);
}

void	rotate(t_ray *ray, t_key *key)
{
	double	tmp_dir;
	double	tmp_plan;

	tmp_dir = ray->dirx;
	tmp_plan = ray->planx;
	if (key->turn_left && !key->turn_right)
		rotate_left(ray, key, tmp_dir, tmp_plan);
	if (key->turn_right && !key->turn_left)
		rotate_right(ray, key, tmp_dir, tmp_plan);
}
