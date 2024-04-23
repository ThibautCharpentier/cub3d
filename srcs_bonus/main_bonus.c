/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:06:23 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/31 19:06:23 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nYou have to run cub3D with ONE argument !\n", 2);
		return (1);
	}
	init_cub(&win);
	parsing_cub(argv[1], &win);
	if (win.map.nbr_x > 99 || win.map.nbr_y > 99)
		print_error("Invalid map: map too wide !\n", &win);
	init_raycasting(&win, &win.map, &win.ray);
	open_window(&win);
	mlx_loop(win.mlx);
	return (0);
}
