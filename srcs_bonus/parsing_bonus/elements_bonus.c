/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:05:09 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/02 14:05:09 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	check_element(char *element, char *line, t_win *win, char **file)
{
	int	type;

	type = -1;
	if (ft_same_str(element, "NO"))
		type = NO;
	else if (ft_same_str(element, "SO"))
		type = SO;
	else if (ft_same_str(element, "WE"))
		type = WE;
	else if (ft_same_str(element, "EA"))
		type = EA;
	else if (ft_same_str(element, "F"))
		type = F;
	else if (ft_same_str(element, "C"))
		type = C;
	free(element);
	if (type < F && type > -1 && !win->map.path[type])
		return (add_texture(type, line, win, file));
	else if (type == F && !win->map.color_f)
		return (add_color(&win->map.color_f, line, win, file));
	else if (type == C && !win->map.color_c)
		return (add_color(&win->map.color_c, line, win, file));
	return (0);
}

static int	check_line(char *line, t_win *win, char **file)
{
	int		i_line;
	char	*element;
	int		len;

	i_line = -1;
	element = NULL;
	len = 0;
	while (line[++i_line] && !element)
	{
		if (ft_isspace(line[i_line]))
			continue ;
		while (line[i_line] && !ft_isspace(line[i_line]))
		{
			i_line++;
			len++;
		}
		element = strlcpy_malloc(line + i_line - len, len + 1, file, win);
		if (!line[i_line])
			break ;
	}
	return (check_element(element, line + i_line, win, file));
}

char	*strlcpy_malloc(char *str, int len, char **file, t_win *win)
{
	char	*s;

	s = malloc(sizeof(char) * len);
	if (!s)
	{
		free_tabstr(file);
		print_error_system("malloc", win);
	}
	ft_strlcpy(s, str, len);
	return (s);
}

int	check_elements(char **file, t_win *win)
{
	int	nb_element;
	int	i_file;

	nb_element = 0;
	i_file = -1;
	while (file[++i_file] && nb_element < 6)
	{
		if (ft_stronlyspace(file[i_file]))
			continue ;
		if (!check_line(file[i_file], win, file))
		{
			free_tabstr(file);
			print_error("File not valid: bad content of elements !\n", win);
		}
		nb_element++;
	}
	if (nb_element != 6)
	{
		free_tabstr(file);
		print_error("File not valid: bad content of elements !\n", win);
	}
	return (i_file);
}
