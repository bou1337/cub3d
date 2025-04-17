#include "../cub3d.h"

char	*extract_path(t_data *data, char *line)
{
    int		i;
    int		j;
    char	*path;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (!is_direction_identifier(line[i], line[i + 1]))
        return (NULL);
    i += 2;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0')
        return (NULL);
    path = allocate_path(line, i);
    if (!path)
        return (NULL);
    j = 0;
    while (line[i] && line[i] != ' ' && line[i] != '\t')
        path[j++] = line[i++];
    path[j] = '\0';
    return (path);
}

int	is_texture(t_data *data, char *line)
{
    int	i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == 'N' && line[i + 1] == 'O')
        return (handle_no_texture(data, line));
    else if (line[i] == 'S' && line[i + 1] == 'O')
        return (handle_so_texture(data, line));
    else if (line[i] == 'W' && line[i + 1] == 'E')
        return (handle_we_texture(data, line));
    else if (line[i] == 'E' && line[i + 1] == 'A')
        return (handle_ea_texture(data, line));
    return (0);
}

int	handle_colors(t_data *data, char *line)
{
    int	r;
    int	g;
    int	b;
    int	result;

    if (!parse_color(line + 1, data))
    {
        free(line);
        return (0);
    }
    if (line[0] == 'C' && line[1] == ' ')
        result = set_ceiling_color(data, line);
    else if (line[0] == 'F' && line[1] == ' ')
        result = set_floor_color(data, line);
    else
        result = 0;
    if (result)
        data->color_index = 1;
    free(line);
    return (result);
}

int	handle_map_line(char *line, t_data *data, char **map, int *i)
{
    char	*padded_line;

    if (data->color_index == 0 || data->texture_index == 0)
    {
        free(line);
        return (0);
    }
    padded_line = pad_line(line);
    free(line);
    if (!padded_line)
        return (0);
    map[*i] = padded_line;
    (*i)++;
    return (1);
}

int	handle_empty_or_space_line(char *line, int j)
{
    if (line[j] == '\0')
    {
        free(line);
        return (1);
    }
    while (line[j] == ' ')
        j++;
    if (line[j] == '\0')
    {
        free(line);
        return (1);
    }
    return (0);
}