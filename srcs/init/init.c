/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:29:41 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/02 14:29:41 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_key(t_win *win)
{
	win->key.up = 0;
	win->key.down = 0;
	win->key.left = 0;
	win->key.right = 0;
	win->key.turn_right = 0;
	win->key.turn_left = 0;
	win->key.movespeed = MOVESPEED;
	win->key.rotspeed = ROTSPEED;
}

void	init_cub(t_win *win)
{
	int	i_tab;

	win->map.map = NULL;
	win->map.color_f = 0;
	win->map.color_c = 0;
	win->map.path = malloc(sizeof(char *) * 5);
	if (!win->map.path)
		print_error_system("malloc", win);
	i_tab = -1;
	while (++i_tab < 5)
		win->map.path[i_tab] = NULL;
	init_key(win);
}
