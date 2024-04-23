/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:43:12 by tcharpen          #+#    #+#             */
/*   Updated: 2022/09/02 13:43:12 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	find_size(char *str, char c, int type)
{
	int	i_str;
	int	size;

	i_str = -1;
	if (type == 0)
	{
		size = 0;
		while (str[++i_str] && str[i_str] != c)
			size++;
		return (size);
	}
	else
	{
		size = 1;
		while (str[++i_str])
		{
			if (str[i_str] == c && str[i_str + 1])
				size++;
		}
		return (size);
	}
}

static char	**free_split_read_file(char **tab)
{
	int	i_tab;

	if (!tab)
		return (NULL);
	i_tab = -1;
	while (tab[++i_tab])
		free(tab[i_tab]);
	free(tab);
	return (NULL);
}

static int	put_str(char *tab, char *str, char c, int i_str)
{
	int	i_tab;

	i_tab = 0;
	while (str[i_str] && str[i_str] != c)
	{
		tab[i_tab] = str[i_str];
		i_str++;
		i_tab++;
	}
	tab[i_tab] = '\0';
	if (str[i_str])
		i_str++;
	return (i_str);
}

static char	**split_read_file(char *str, char c)
{
	int		size_tab;
	char	**tab;
	int		i_tab;
	int		i_str;
	int		size_str;

	if (!str)
		return (NULL);
	size_tab = find_size(str, c, 1);
	tab = malloc(sizeof(char *) * (size_tab + 1));
	if (!tab)
		return (NULL);
	tab[size_tab] = NULL;
	i_tab = -1;
	i_str = 0;
	while (++i_tab < size_tab)
	{
		size_str = find_size(str + i_str, c, 0);
		tab[i_tab] = malloc(sizeof(char) * (size_str + 1));
		if (!tab[i_tab])
			return (free_split_read_file(tab));
		i_str = put_str(tab[i_tab], str, c, i_str);
	}
	return (tab);
}

char	**read_file(int fd)
{
	char	*tmp;
	char	*str;
	char	**file;

	tmp = ft_calloc(1, 1);
	if (!tmp)
		return (NULL);
	str = ft_strdup(tmp);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	while (tmp)
	{
		str = ft_strjoin_free_s1(str, tmp);
		free(tmp);
		if (!str)
			return (NULL);
		tmp = get_next_line(fd);
	}
	file = split_read_file(str, '\n');
	free(str);
	return (file);
}
