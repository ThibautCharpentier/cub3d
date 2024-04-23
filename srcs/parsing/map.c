/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:13:48 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/08 12:13:48 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_line(char *line, int *size_map, int *size_line)
{
	int	i_line;
	int	len_line;

	i_line = -1;
	len_line = 0;
	while (line[++i_line])
	{
		if (line[i_line] != '1' && line[i_line] != '0' && line[i_line] != ' '
			&& line[i_line] != 'N' && line[i_line] != 'S'
			&& line[i_line] != 'E' && line[i_line] != 'W')
			return (0);
		len_line++;
	}
	if (len_line > *size_line)
		*size_line = len_line;
	*size_map = *size_map + 1;
	return (1);
}

static int	check_lines_after_map(char **file, char **file_to_free)
{
	int	i_file;

	i_file = -1;
	while (file[++i_file])
	{
		if (!ft_stronlyspace(file[i_file]))
		{
			free_tabstr(file_to_free);
			return (0);
		}
	}
	return (1);
}

static void	add_line(char *line, char *str, int size_line)
{
	int	i_line;

	i_line = -1;
	while (str[++i_line])
		line[i_line] = str[i_line];
	while (i_line < size_line)
		line[i_line++] = ' ';
	line[size_line] = '\0';
}

static int	init_map(char **file, int size_map, int size_line, t_win *win)
{
	int	i_map;
	int	i_file;

	win->map.map = malloc(sizeof(char *) * (size_map + 1));
	if (!win->map.map)
		return (0);
	win->map.map[size_map] = NULL;
	i_map = -1;
	i_file = 0;
	while (++i_map < size_map)
	{
		win->map.map[i_map] = malloc(sizeof(char) * (size_line + 1));
		if (!win->map.map[i_map])
			return (0);
		add_line(win->map.map[i_map], file[i_file++], size_line);
	}
	win->map.nbr_x = size_line;
	win->map.nbr_y = size_map;
	return (1);
}

void	check_map(char **file, int i_file, t_win *win)
{
	int	size_map;
	int	size_line;
	int	i_tmp;

	while (file[i_file] && ft_stronlyspace(file[i_file]))
		i_file++;
	i_tmp = i_file;
	size_map = 0;
	size_line = 0;
	while (file[i_file] && !ft_stronlyspace(file[i_file]))
	{
		if (!check_line(file[i_file], &size_map, &size_line))
		{
			free_tabstr(file);
			print_error("Invalid map: forbidden character found !\n", win);
		}
		i_file++;
	}
	if (!check_lines_after_map(file + i_file, file))
		print_error("File not valid: too many elements !\n", win);
	if (!init_map(file + i_tmp, size_map, size_line, win))
	{
		free_tabstr(file);
		print_error_system("malloc", win);
	}
}
