/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:22:54 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/01 13:22:54 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *str, t_win *win)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	free_cub(win, EXIT_FAILURE);
}

void	print_error_system(char *str, t_win *win)
{
	ft_putstr_fd("Error\n", 2);
	perror(str);
	free_cub(win, EXIT_FAILURE);
}
