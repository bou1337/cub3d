/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:46:27 by hfazaz            #+#    #+#             */
/*   Updated: 2025/03/19 03:35:35 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strlen(char *str)
{
    int	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int		check_extension(const char *filename)
{
    int	len;

    len = ft_strlen((char *)filename);
    if (len < 4)
        return (0);
    if (filename[len - 4] != '.' || filename[len - 3] != 'c'
        || filename[len - 2] != 'u' || filename[len - 1] != 'b')
        return (0);
    return (1);
}

char	*get_line(int fd)
{
    char	*line;
    int		i;

    i = 0;
    line = malloc(sizeof(char) * 2147483647);
    if (!line)
        return (NULL);
    while (read(fd, &line[i], 1))
    {
        if (line[i] == '\n')
        {
            line[i] = '\0';
            return (line);
        }
        i++;
    }
    if (i > 0)
    {
        line[i] = '\0';
        return (line);
    }
    free(line);
    return (NULL);
}

int		is_map_line(char *line)
{
    int	i;

    i = 0;
    if (!line || !line[0])
        return (0);
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
            && line[i] != '2' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'W' && line[i] != 'E')
            return (0);
        i++;
    }
    return (1);
}


static int	get_max_len(char **map)
{
    int	i;
    int	max;
    int	len;

    i = 0;
    max = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        if (len > max)
            max = len;
        i++;
    }
    return (max);
}

static char	*pad_line(char *line, int max_len)
{
    int		i;
    int		len;
    char	*new_line;
    char	fill;

    len = ft_strlen(line);
    new_line = malloc(sizeof(char) * (max_len + 1));
    if (!new_line)
        return (NULL);
    i = 0;
    while (i < len)
    {
        new_line[i] = line[i];
        i++;
    }
    fill = (line[len - 1] == '1') ? '1' : ' ';
    while (i < max_len)
        new_line[i++] = fill;
    new_line[i] = '\0';
    return (new_line);
}

char	**pad_map(char **map)
{
    int		i;
    int		row;
    int		max_len;
    char	**padded;

    row = 0;
    while (map[row])
        row++;
    max_len = get_max_len(map);
    padded = malloc(sizeof(char *) * (row + 1));
    if (!padded)
        return (NULL);
    i = 0;
    while (i < row)
    {
        padded[i] = pad_line(map[i], max_len);
        if (!padded[i])
            return (NULL);
        i++;
    }
    padded[i] = NULL;
    return (padded);
}

int		parse_int(const char *str, int *i)
{
    int	num;
    int	sign;

    num = 0;
    sign = 1;
    while (str[*i] == ' ' || str[*i] == '\t')
        (*i)++;
    if (str[*i] == '-')
    {
        sign = -1;
        (*i)++;
    }
    while (str[*i] >= '0' && str[*i] <= '9')
    {
        num = num * 10 + (str[*i] - '0');
        (*i)++;
    }
    return (sign * num);
}

int		parse_color(char *line, int *r, int *g, int *b)
{
    int	i;
    
    i = 1;
    *r = parse_int(line, &i);
    if (*r < 0 || *r > 255)
        return (0);
    if (line[i] == ',')
        i++;
    *g = parse_int(line, &i);
    if (*g < 0 || *g > 255)
        return (0);
    if (line[i] == ',')
        i++;
    *b = parse_int(line, &i);
    if (*b < 0 || *b > 255)
        return (0);
    return (1);
}




 char *extract_path(t_data *data, char *line)
{
    int  i;
    int  start;
    char *path;
    int  fd;

    start = 2;
    while (line[start] && line[start] == ' ')
        start++;
    i = start;
    while (line[i] && line[i] != ' ')
        i++;
    if (i == start)
        return (0);
    path = malloc(sizeof(char) * (i - start + 1));
    if (!path)
        return (0);
    i = 0;
    while (line[start] && line[start] != ' ')
    {
        path[i] = line[start];
        i++;
        start++;
    }
    path[i] = '\0';
    return path;
}

static int is_texture(t_data *data, char *line)
{
    if(line[0] == 'N' && line[1] == 'O')
        data->textures_path[0] = extract_path(data, line);
    else if(line[0] == 'S' && line[1] == 'O')
        data->textures_path[2] = extract_path(data, line);
    else if(line[0] == 'W' && line[1] == 'E')
        data->textures_path[3] = extract_path(data, line);
    else if(line[0] == 'E' && line[1] == 'A')
        data->textures_path[1] = extract_path(data, line);
    return (0);
}

static int	read_config_lines(int fd, t_data *data, char **map, int *i)
{
    char	*line;
    int		r;
    int		g;
    int		b;

    while ((line = get_line(fd)))
    {
        if (line[0] == 'C')
        {
            data->pos++;
            if (!parse_color(line, &r, &g, &b))
            {
                fprintf(stderr, "Error: Invalid ceiling color\n");
                free(line);
                return (0);
            }
            data->textures.ceil_color = (r << 16) | (g << 8) | b;
            free(line);
        }
        else if (line[0] == 'F')
        {
            data->pos++;
            if (!parse_color(line, &r, &g, &b))
            {
                fprintf(stderr, "Error: Invalid floor color\n");
                free(line);
                return (0);
            }
            data->textures.floor_color = (r << 16) | (g << 8) | b;
            free(line);
        }
        else if(is_texture(data,line))
        {
            data->pos++;
            
        }
        else if (is_map_line(line))
        {
            // data->pos++;
            map[*i] = line;
            (*i)++;
            return (1);
        }
        else
            free(line);
    }
    return (0);
}


static void	read_map_lines(int fd, char **map, int *i)
{
    char	*line;

    while ((line = get_line(fd)))
    {
        if (!is_map_line(line))
        {
            free(line);
            break ;
        }
        map[*i] = line;
        (*i)++;
    }
    map[*i] = NULL;
}


char	**read_cub_file(int fd, t_data *data)
{
    char	**map;
    int		i;
    
    // data->pos = 0;
    i = 0;
    map = malloc(sizeof(char *) * 2147483647);
    if (!map)
        return (NULL);
    if (!read_config_lines(fd, data, map, &i))
    {
        free(map);
        return (NULL);
    }
    read_map_lines(fd, map, &i);
    return (pad_map(map));
}

void	map_size(t_data *data)
{
    int		h;
    int		w;
    int		i;
    char	**map;

    h = 0;
    i = 0;
    map = data->map.map;
    while (map[i])
    {
        h++;
        i++;
    }
    w = ft_strlen(map[0]);
    data->map.height = h;
    data->map.width = w;
}

int		check_top_bottom(char **map, int size)
{
    int	i;

    i = 0;
    while (map[0][i])
    {
        if (map[0][i] != '1')
            return (0);
        i++;
    }
    i = 0;
    while (map[size - 1][i])
    {
        if (map[size - 1][i] != '1')
            return (0);
        i++;
    }
    return (1);
}

int		check_borders(char **map)
{
    int	i;
    int	len;
    int	size_map;

    size_map = 0;
    while (map[size_map])
        size_map++;
    if (!check_top_bottom(map, size_map))
        return (0);
    i = 1;
    while (i < size_map - 1)
    {
        len = ft_strlen(map[i]);
        if (map[i][0] != '1' || map[i][len - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}

int		valid_map(char **map)
{
    return (check_borders(map));
}


void	set_player_data(t_data *data)
{
    int	i;
    int	j;

    i = 0;
    while (data->map.map[i])
    {
        j = 0;
        while (data->map.map[i][j])
        {
            if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S'
                || data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
            {
                data->player.pos_x = j;
                data->player.pos_y = i;
                if (data->map.map[i][j] == 'N')
                    data->player.angle = 3 * M_PI / 2;
                else if (data->map.map[i][j] == 'S')
                    data->player.angle = M_PI / 2;
                else if (data->map.map[i][j] == 'E')
                    data->player.angle = 0;
                else if (data->map.map[i][j] == 'W')
                    data->player.angle = M_PI;
                data->map.map[i][j] = '0';
                return ;
            }
            j++;
        }
        i++;
    }
}


static int	check_color_range(int color)
{
    int	r;
    int	g;
    int	b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (0);
    return (1);
  
}
int	check_config_data(t_data *data)
{
    if (data->textures.ceil_color == -1 ||
        data->textures.floor_color == -1)
    {
        fprintf(stderr,
            "Error: Missing floor or ceiling color configuration\n");
        return (0);
    }
    if (!check_color_range(data->textures.ceil_color))
    {
        fprintf(stderr, "Error: Ceiling color invalid\n");
        return (0);
    }
    if (!check_color_range(data->textures.floor_color))
    {
        fprintf(stderr, "Error: Floor color invalid\n");
        return (0);
    }
    return (1);
}


int	main(int argc, char **argv)
{
    int		fd;
    char	**map;
    t_data	data;
    int		i;

    data.textures.ceil_color = -1;
    data.textures.floor_color = -1;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s map.cub\n", argv[0]);
        return (1);
    }
    if (!check_extension(argv[1]))
    {
        fprintf(stderr, "Error: File must have a .cub extension\n");
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }
    map = read_cub_file(fd, &data);
    data.map.map = map;
    close(fd);
    if (!map)
    {
        fprintf(stderr, "Failed to load map\n");
        return (1);
    }
    if (!check_config_data(&data))
        return (1);
    if (!valid_map(map))
    {
        fprintf(stderr, "Invalid map format\n");
        return (1);
    }
    set_player_data(&data);
    map_size(&data);
    printf("Map is valid.\n");
    printf("Player position: (%f, %f)  Angle: %f\n", data.player.pos_x, \
data.player.pos_y, data.player.angle);
    i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        free(map[i]);
        i++;
    }
    printf("Map height: %d  width: %d\n", data.map.height, data.map.width);
    printf("Ceiling color: %06X  Floor color: %06X\n", data.textures.ceil_color, \
data.textures.floor_color);
printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", data.textures_path[0], data.textures_path[2], data.textures_path[3], data.textures_path[1]);
    free(map);
    return (0);
}
