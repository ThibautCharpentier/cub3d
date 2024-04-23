/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tabstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:27:47 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/03 13:27:47 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	free_tabstr(char **tab)
{
	int	i_tab;

	if (!tab)
		return ;
	i_tab = -1;
	while (tab[++i_tab])
		free(tab[i_tab]);
	free(tab);
}
