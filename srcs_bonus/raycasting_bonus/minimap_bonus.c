/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:33:11 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/25 11:33:11 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	check_put_pixel(t_mini *mini, t_map *map)
{
	if (mini->posx < 0 || mini->posx >= map->nbr_x
		|| mini->posy < 0 || mini->posy >= map->nbr_y)
		return (0);
	return (1);
}

static int	check_position_player(t_mini *mini, t_ray *ray)
{
	double	distx;
	double	disty;
	double	dist;

	distx = (mini->posx - ray->posx) * (mini->posx - ray->posx);
	disty = (mini->posy - ray->posy) * (mini->posy - ray->posy);
	dist = sqrt(distx + disty);
	if (dist < 0.3)
		return (1);
	return (0);
}

static int	find_color_pixel(t_mini *mini, t_map *map, t_ray *ray)
{
	int	tmpx;
	int	tmpy;

	tmpx = (int) mini->posx;
	tmpy = (int) mini->posy;
	if (check_position_player(mini, ray))
		return (0xEE2626);
	else if (map->map[tmpy][tmpx] == '1')
		return (0xA0A0A0);
	else if (map->map[tmpy][tmpx] == '2')
		return (0xFFD800);
	else if (map->map[tmpy][tmpx] == '4')
		return (0xFF9300);
	else
		return (0);
}

void	load_minimap(t_win *win, t_ray *ray, t_mini *mini, t_map *map)
{
	int	color;
	int	x;
	int	y;

	x = 0;
	mini->posx = ray->posx - 4.0;
	while (x <= mini->size)
	{
		y = 0;
		mini->posy = ray->posy - 4.0;
		while (y <= mini->size)
		{
			if (check_put_pixel(mini, map))
			{
				color = find_color_pixel(mini, map, ray);
				if (color > 0)
					my_mlx_pixel_put(win->img_actual, x, y, color);
			}
			y++;
			mini->posy = mini->posy + mini->step;
		}
		x++;
		mini->posx = mini->posx + mini->step;
	}
}
