/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:30:22 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/31 18:30:22 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	key_press(int keycode, t_win *win)
{
	if (keycode == ESC)
	{
		ft_putstr_fd("Program has been closed !\n", 1);
		destroy_img(win);
		mlx_destroy_window(win->mlx, win->win);
		free_cub(win, EXIT_SUCCESS);
	}
	else if (keycode == UP)
		win->key.up = 1;
	else if (keycode == DOWN)
		win->key.down = 1;
	else if (keycode == LEFT)
		win->key.left = 1;
	else if (keycode == RIGHT)
		win->key.right = 1;
	else if (keycode == TURN_LEFT)
		win->key.turn_left = 1;
	else if (keycode == TURN_RIGHT)
		win->key.turn_right = 1;
	else if (keycode == SPACE)
		open_door(win);
	return (0);
}

int	key_release(int keycode, t_win *win)
{
	if (keycode == UP)
		win->key.up = 0;
	else if (keycode == DOWN)
		win->key.down = 0;
	else if (keycode == LEFT)
		win->key.left = 0;
	else if (keycode == RIGHT)
		win->key.right = 0;
	else if (keycode == TURN_LEFT)
		win->key.turn_left = 0;
	else if (keycode == TURN_RIGHT)
		win->key.turn_right = 0;
	return (0);
}

int	mouse_move(int x, int y, t_win *win)
{
	int	min_right;
	int	min_left;

	(void) y;
	min_right = (MAX_WIDTH / 4) * 3;
	min_left = (MAX_WIDTH / 4);
	if (x > min_right)
	{
		win->key.turn_right = 1;
		win->key.turn_left = 0;
	}
	else if (x < min_left)
	{
		win->key.turn_left = 1;
		win->key.turn_right = 0;
	}
	else
	{
		win->key.turn_left = 0;
		win->key.turn_right = 0;
	}
	return (0);
}

int	destroy_window(t_win *win)
{
	ft_putstr_fd("Program has been closed !\n", 1);
	destroy_img(win);
	mlx_destroy_window(win->mlx, win->win);
	free_cub(win, EXIT_SUCCESS);
	return (0);
}

void	open_window(t_win *win)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		print_error_system("mlx_init", win);
	win->win = mlx_new_window(win->mlx, MAX_WIDTH, MAX_HEIGHT, "cub3D");
	if (!win->win)
		print_error_system("mlx_new_window", win);
	init_image(win);
	mlx_hook(win->win, 17, 0, destroy_window, win);
	mlx_hook(win->win, 2, 1L << 0, key_press, win);
	mlx_hook(win->win, 3, 1L << 1, key_release, win);
	mlx_hook(win->win, 6, 1L << 6, mouse_move, win);
	mlx_loop_hook(win->mlx, raycasting, win);
}
