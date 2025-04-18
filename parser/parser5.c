/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:48:51 by hfazaz            #+#    #+#             */
/*   Updated: 2025/04/18 16:48:52 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	process_config_line(char *line, t_data *data, char **map, int *i)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j] == '\0' || (line[j] == ' ' && handle_empty_or_space_line(line,
				j)))
		return (1);
	if (line[j] == 'C' || line[j] == 'F')
		return (handle_colors(data, line));
	else if (is_texture(data, line))
	{
		data->texture_index = 1;
		return (1);
	}
	else if (is_map_line(line))
	{
		data->map_found = 1;
		return (handle_map_line(line, data, map, i));
	}
	free(line);
	return (0);
}

int	read_config_lines(int fd, t_data *data, char **map, int *i)
{
	char	*line;

	while ((line = get_line(fd)))
	{
		if ((!process_config_line(line, data, map, i)))
			return (0);
		if (*i > 0)
			return (1);
	}
	return (0);
}

int	check_empty_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\t')
		{
			free(line);
			return (0);
		}
		j++;
	}
	free(line);
	return (1);
}

int	read_remaining_lines(int fd)
{
	char	*line;
	int		j;

	while ((line = get_line(fd)))
	{
		j = 0;
		while (line[j])
		{
			if (line[j] != ' ' && line[j] != '\t')
			{
				free(line);
				return (0);
			}
			j++;
		}
		free(line);
	}
	return (1);
}

int	read_map_lines(int fd, char **map, int *i)
{
	char *line;

	while ((line = get_line(fd)))
	{
		if (!is_map_line(line))
		{
			if (!check_empty_line(line))
				return (0);
			if (!read_remaining_lines(fd))
				return (0);
			break ;
		}
		line = pad_line(line);
		map[*i] = line;
		(*i)++;
	}
	map[*i] = NULL;
	return (1);
}