/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:32:23 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/02 14:32:23 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_cub(t_win *win, int id_exit)
{
	free_tabstr(win->map.map);
	free(win->map.path[NO]);
	free(win->map.path[SO]);
	free(win->map.path[WE]);
	free(win->map.path[EA]);
	free(win->map.path);
	exit(id_exit);
}
