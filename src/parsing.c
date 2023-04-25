/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:27:34 by avast             #+#    #+#             */
/*   Updated: 2023/01/04 16:59:14 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/params.h"
#include "../includes/proto.h"
#include "../libft/libft.h"

int	count_columns(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (*line && (*line == 32 || *line == 10))
			line++;
		if (*line && *line != 32 && *line != 10)
			count++;
		while (*line && *line != 32 && *line != 10)
			line++;
	}
	return (count);
}

t_altcol	*get_coor_3d(char	*line, int size_x, t_data *data)
{
	t_altcol	*tab;
	int			i;

	tab = malloc(sizeof(t_altcol) * size_x);
	if (!tab)
		return (0);
	i = 0;
	while (i < size_x)
	{
		while (*line && (*line == 32 || *line == 10))
			line++;
		if (*line && *line != 32 && *line != 10)
		{
			tab[i] = ft_atoi_fdf(line);
			if (ft_abs(tab[i].z) > (*data).max_alti)
				(*data).max_alti = ft_abs(tab[i].z);
		}
		while (*line && *line != 32 && *line != 10)
			line++;
		i++;
	}
	return (tab);
}

t_altcol	**realloc_tab(t_altcol **tab, char *line, t_data *data)
{
	t_altcol	**new_tab;
	int			i;

	if (!tab)
		new_tab = malloc(sizeof(t_altcol *) * 1);
	else
		new_tab = malloc(sizeof(t_altcol *) * ((*data).size.y + 1));
	if (!new_tab)
		return (0);
	i = 0;
	while (i < (*data).size.y - 1 && tab)
	{
		new_tab[i] = malloc(sizeof(t_altcol) * (*data).size.x);
		if (!new_tab[i])
			return (free_tab_altcol(new_tab, i - 1), (t_altcol **)0);
		new_tab[i] = ft_memcpy_fdf(new_tab[i], tab[i], (*data).size.x);
		i++;
	}
	new_tab[i] = get_coor_3d(line, (*data).size.x, data);
	if (!new_tab[i])
		return (free_tab_altcol(new_tab, i - 1), (t_altcol **)0);
	if (tab)
		free_tab_altcol(tab, (*data).size.y - 2);
	return (new_tab);
}

t_altcol	**read_map(t_data *data)
{
	t_altcol	**map;
	int			fd;
	char		*line;

	map = 0;
	(*data).size.y = 0;
	fd = open((*data).file, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		close_window(data);
	}
	line = get_next_line(fd);
	(*data).size.x = count_columns(line);
	while (line)
	{
		(*data).size.y = (*data).size.y + 1;
		map = realloc_tab(map, line, data);
		if (!map)
			return (free_tab_altcol(map, ((*data).size.y - 1)), (t_altcol **)0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), map);
}
