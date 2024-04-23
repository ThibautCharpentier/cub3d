/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:46:03 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/07 15:46:03 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int	*dst;

	dst = img->addr + (y * img->line_length / 4 + x);
	*(unsigned int *) dst = color;
}

static void	ver_line(t_win *win, t_img *txt, t_draw *draw, int x)
{
	int	y;
	int	color;

	y = -1;
	while (++y < draw->start)
		my_mlx_pixel_put(win->img_actual, x, y, win->map.color_c);
	while (y <= draw->end)
	{
		draw->tex_y = (int)(draw->tex_pos);
		draw->tex_pos = draw->tex_pos + draw->step;
		color = txt->addr[draw->tex_y * txt->line_length / 4 + draw->tex_x];
		my_mlx_pixel_put(win->img_actual, x, y++, color);
	}
	while (y < MAX_HEIGHT)
		my_mlx_pixel_put(win->img_actual, x, y++, win->map.color_f);
}

static void	calcul_texture(t_ray *ray, t_math *math, t_draw *draw, t_img *txt)
{
	draw->line_height = (int)(MAX_HEIGHT / math->perpwalldist);
	draw->start = -draw->line_height / 2 + MAX_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + MAX_HEIGHT / 2;
	if (draw->end >= MAX_HEIGHT)
		draw->end = MAX_HEIGHT - 1;
	if (math->side == 0)
		draw->wall = ray->posy + math->perpwalldist * ray->ray_diry;
	else
		draw->wall = ray->posx + math->perpwalldist * ray->ray_dirx;
	draw->wall -= floor(draw->wall);
	draw->tex_x = (int)(draw->wall * (double) txt->width);
	if (math->side == 0 && ray->ray_dirx > 0)
		draw->tex_x = txt->width - draw->tex_x - 1;
	else if (math->side == 1 && ray->ray_diry < 0)
		draw->tex_x = txt->width - draw->tex_x - 1;
	draw->step = 1.0 * txt->height / draw->line_height;
	draw->tex_pos = (draw->start - MAX_HEIGHT / 2 + draw->line_height / 2)
		* draw->step;
}

void	calcul_draw(t_ray *ray, t_math *math, t_win *win, int x)
{
	if (math->side == 0 && ray->ray_dirx > 0)
		win->texture = &win->we;
	else if (math->side == 0 && ray->ray_dirx < 0)
		win->texture = &win->ea;
	else if (math->side == 1 && ray->ray_diry > 0)
		win->texture = &win->no;
	else if (math->side == 1 && ray->ray_diry < 0)
		win->texture = &win->so;
	calcul_texture(ray, math, &ray->draw, win->texture);
	ver_line(win, win->texture, &ray->draw, x);
}
