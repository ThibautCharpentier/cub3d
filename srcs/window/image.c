/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:51:08 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/31 18:51:08 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*image(t_img *img, void *mlx, char *path)
{
	return (mlx_xpm_file_to_image(mlx, path, &img->width, &img->height));
}

void	init_image(t_win *win)
{
	win->no.img = image(&win->no, win->mlx, win->map.path[NO]);
	win->so.img = image(&win->so, win->mlx, win->map.path[SO]);
	win->we.img = image(&win->we, win->mlx, win->map.path[WE]);
	win->ea.img = image(&win->ea, win->mlx, win->map.path[EA]);
	if (!win->no.img || !win->so.img || !win->we.img
		|| !win->ea.img)
	{
		mlx_destroy_window(win->mlx, win->win);
		print_error_system("image", win);
	}
	win->no.addr = (int *) mlx_get_data_addr(win->no.img,
			&win->no.bits_per_pixel, &win->no.line_length, &win->no.endian);
	win->so.addr = (int *) mlx_get_data_addr(win->so.img,
			&win->so.bits_per_pixel, &win->so.line_length, &win->so.endian);
	win->we.addr = (int *) mlx_get_data_addr(win->we.img,
			&win->we.bits_per_pixel, &win->we.line_length, &win->we.endian);
	win->ea.addr = (int *) mlx_get_data_addr(win->ea.img,
			&win->ea.bits_per_pixel, &win->ea.line_length, &win->ea.endian);
}

void	destroy_img(t_win *win)
{
	mlx_destroy_image(win->mlx, win->no.img);
	mlx_destroy_image(win->mlx, win->so.img);
	mlx_destroy_image(win->mlx, win->we.img);
	mlx_destroy_image(win->mlx, win->ea.img);
}
