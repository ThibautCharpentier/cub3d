/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:41:49 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/07 12:41:49 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	calcul_side_step(t_ray *ray, t_math *math)
{
	if (ray->ray_dirx < 0)
	{
		math->stepx = -1;
		math->side_distx = (ray->posx - ray->mapx) * math->delta_distx;
	}
	else
	{
		math->stepx = 1;
		math->side_distx = (ray->mapx + 1.0 - ray->posx) * math->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		math->stepy = -1;
		math->side_disty = (ray->posy - ray->mapy) * math->delta_disty;
	}
	else
	{
		math->stepy = 1;
		math->side_disty = (ray->mapy + 1.0 - ray->posy) * math->delta_disty;
	}
}

static void	dda_algorithm(char **map, t_ray *ray, t_math *math)
{
	while (math->hit == 0)
	{
		if (math->side_distx < math->side_disty)
		{
			math->side_distx += math->delta_distx;
			ray->mapx += math->stepx;
			math->side = 0;
		}
		else
		{
			math->side_disty += math->delta_disty;
			ray->mapy += math->stepy;
			math->side = 1;
		}
		math->hit = is_hit(map[ray->mapy][ray->mapx]);
	}
	if (math->side == 0)
		math->perpwalldist = (ray->mapx - ray->posx + (1 - math->stepx) / 2)
			/ ray->ray_dirx;
	else
		math->perpwalldist = (ray->mapy - ray->posy + (1 - math->stepy) / 2)
			/ ray->ray_diry;
}

static void	init_actual_ray(t_ray *ray, t_math *math)
{
	ray->ray_dirx = ray->dirx + ray->planx * ray->camerax;
	ray->ray_diry = ray->diry + ray->plany * ray->camerax;
	if (ray->ray_diry == 0)
		math->delta_disty = 1e30;
	else
		math->delta_disty = sqrt(1 + ray->ray_dirx * ray->ray_dirx
				/ (ray->ray_diry * ray->ray_diry));
	if (ray->ray_dirx == 0)
		math->delta_distx = 1e30;
	else
		math->delta_distx = sqrt(1 + ray->ray_diry * ray->ray_diry
				/ (ray->ray_dirx * ray->ray_dirx));
	ray->mapx = (int) ray->posx;
	ray->mapy = (int) ray->posy;
	math->hit = 0;
	math->door = 0;
}

static void	switch_img(t_win *win, int *img)
{
	if (*img == 1)
	{
		if (win->img_one.img != NULL)
			mlx_destroy_image(win->mlx, win->img_one.img);
		win->img_one.img = mlx_new_image(win->mlx, MAX_WIDTH, MAX_HEIGHT);
		if (!win->img_one.img)
			print_error_system("mlx_new_img", win);
		win->img_one.addr = (int *) mlx_get_data_addr(win->img_one.img,
				&win->img_one.bits_per_pixel, &win->img_one.line_length,
				&win->img_one.endian);
		win->img_actual = &win->img_one;
	}
	else
	{
		if (win->img_two.img != NULL)
			mlx_destroy_image(win->mlx, win->img_two.img);
		win->img_two.img = mlx_new_image(win->mlx, MAX_WIDTH, MAX_HEIGHT);
		if (!win->img_two.img)
			print_error_system("mlx_new_img", win);
		win->img_two.addr = (int *) mlx_get_data_addr(win->img_two.img,
				&win->img_two.bits_per_pixel, &win->img_two.line_length,
				&win->img_two.endian);
		win->img_actual = &win->img_two;
	}
}

int	raycasting(t_win *win)
{
	int			x;
	static int	img = 1;

	switch_img(win, &img);
	x = 0;
	while (x != MAX_WIDTH)
	{
		win->ray.camerax = 2 * x / ((double) MAX_WIDTH) - 1;
		position_player_at_door(&win->ray, win->map.map);
		init_actual_ray(&win->ray, &win->ray.math);
		calcul_side_step(&win->ray, &win->ray.math);
		dda_algorithm(win->map.map, &win->ray, &win->ray.math);
		calcul_draw(&win->ray, &win->ray.math, win, x);
		x++;
	}
	load_minimap(win, &win->ray, &win->ray.mini, &win->map);
	move(&win->ray, &win->key, win->map.map);
	rotate(&win->ray, &win->key);
	mlx_put_image_to_window(win->mlx, win->win, win->img_actual->img, 0, 0);
	if (img == 1)
		img++;
	else
		img--;
	return (0);
}
