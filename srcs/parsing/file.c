/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:27:56 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/01 13:27:56 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_name_file(char *file)
{
	int	i_file;

	if (ft_strlen(file) <= 4)
		return (0);
	i_file = -1;
	while (file[++i_file])
	{
		if (file[i_file] == '.' && ft_strlen(file + i_file) == 4)
		{
			if (file[i_file + 1] == 'c' && file[i_file + 2] == 'u'
				&& file[i_file + 3] == 'b')
				return (1);
		}
	}
	return (0);
}

char	**check_file(char *arg, t_win *win)
{
	int		fd;
	char	**file;

	if (!check_name_file(arg))
		print_error("File not valid: it must have '*.cub' extension !\n", win);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		print_error_system("open file", win);
	file = read_file(fd);
	if (close(fd) < 0 || !file)
	{
		free_tabstr(file);
		print_error_system("read_file", win);
	}
	return (file);
}
