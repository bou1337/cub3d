/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:46:27 by hfazaz            #+#    #+#             */
/*   Updated: 2025/04/05 21:34:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
    int	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int	check_extension(const char *filename)
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
    line = malloc(sizeof(char) * 100);
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

int	is_valid_map_char(char c)
{
    return (c == ' ' || c == '0' || c == '1' || c == '2' || 
        c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	is_map_line(char *line)
{
    int	i;

    i = 0;
    if (!line || !line[0])
        return (0);
    while (line[i] == ' ')
        i++;
    if (!line[i])
        return (0);
    i = 0;
    while (line[i])
    {
        if (!is_valid_map_char(line[i]))
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

static char	*pad_line(char *line)
{
    int		i;
    int		len;
    char	*padded;

    len = ft_strlen(line);
    padded = malloc(sizeof(char) * (len + 1));
    if (!padded)
        return (NULL);
    i = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            padded[i] = '2';
        else
            padded[i] = line[i];
        i++;
    }
    padded[i] = '\0';
    return (padded);
}

int	parse_int(const char *str, int *i)
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

int	parse_color(char *line, int *r, int *g, int *b)
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

char	*extract_path(t_data *data, char *line)
{
    int		i;
    int		start;
    char	*path;

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
    return (path);
}

static int	is_texture(t_data *data, char *line)
{
    if (line[0] == 'N' && line[1] == 'O')
        data->textures_path[0] = extract_path(data, line);
    else if (line[0] == 'S' && line[1] == 'O')
        data->textures_path[2] = extract_path(data, line);
    else if (line[0] == 'W' && line[1] == 'E')
        data->textures_path[3] = extract_path(data, line);
    else if (line[0] == 'E' && line[1] == 'A')
        data->textures_path[1] = extract_path(data, line);
    else
        return (0);
    return (1);
}

static int	handle_colors(t_data *data, char *line)
{
    int	r;
    int	g;
    int	b;

    if (!parse_color(line + 1, &r, &g, &b))
    {
        fprintf(stderr, "Error: Invalid color\n");
        free(line);
        return (0);
    }
    if (line[0] == 'C')
        data->textures.ceil_color = (r << 16) | (g << 8) | b;
    else
        data->textures.floor_color = (r << 16) | (g << 8) | b;
    data->color_index = 1;
    free(line);
    return (1);
}

static int	handle_map_line(char *line, t_data *data, char **map, int *i)
{
    char	*padded_line;

    if (data->color_index == 0 || data->texture_index == 0)
    {
        fprintf(stderr, "Map should be at the end of file\n");
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

static int	process_config_line(char *line, t_data *data, char **map, int *i)
{
    if (line[0] == 'C' || line[0] == 'F')
        return (handle_colors(data, line));
    else if (is_texture(data, line))
    {
        data->texture_index = 1;
        return (1);
    }
    else if (is_map_line(line))
        return (handle_map_line(line, data, map, i));
    else
    {
        free(line);
        return (1);
    }
}

static int	read_config_lines(int fd, t_data *data, char **map, int *i)
{
    char	*line;

    while ((line = get_line(fd)))
    {
        if (!process_config_line(line, data, map, i))
            return (0);
        if (*i > 0)
            return (1);
    }
    return (0);
}

static void read_map_lines(int fd, char **map, int *i)
{
    char *line;

    while ((line = get_line(fd)))
    {
        if (!is_map_line(line))
        {
            free(line);
            break;
        }
        line = pad_line(line);
        map[*i] = line;
        (*i)++;
    }
    map[*i] = NULL;
}


int	map_len(int fd)
{
    int		len;
    char	*line;

    len = 0;
    while ((line = get_line(fd)))
    {
        if (is_map_line(line))
            len++;
        free(line);
    }
    return (len);
}


static int	allocate_map(char ***map, int map_length)
{
    *map = malloc(sizeof(char *) * (map_length + 1));
    if (!(*map))
        return (0);
    return (1);
}

static int	process_map_data(int fd, t_data *data, char **map)
{
    int	i;

    i = 0;
    if (!read_config_lines(fd, data, map, &i))
    {
        free(map);
        return (0);
    }
    read_map_lines(fd, map, &i);
    if (i == 0)
    {
        fprintf(stderr, "Error: No valid map data found\n");
        free(map);
        return (0);
    }
    return (1);
}

char	**read_cub_file(int fd, t_data *data)
{
    char	**map;
    int		map_length;

    map_length = map_len(fd);
    if (map_length == 0)
    {
        fprintf(stderr, "Error: Empty map file or no valid map lines\n");
        return (NULL);
    }
    if (!allocate_map(&map, map_length))
        return (NULL);
    close(fd);
    fd = open("map.cub", O_RDONLY);
    if (fd < 0)
    {
        free(map);
        perror("open");
        return (NULL);
    }
    if (!process_map_data(fd, data, map))
        return (NULL);
    return (map);
}

void map_size(t_data *data)
{
    int h;
    int w;
    int i;
    char **map;

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

int check_top_bottom(char **map)
{
    int i;
    int j;
    
    i = 0;
    
    while (map[i][j])
    {
        j = 0;
       if(map[i][j] == 2 )
       {
            while(map[i][j])
            {
                if(map[i++][j] == '0' || map[i++][j] == '2')
                    continue;
                if(!map)
                    return 0;
                else 
                    return 1;
            }
       }
    }
    return 0;
}

int check_borders(char **map)
{
    int i;
    int len;
    int size_map;

    size_map = 0;
    while (map[size_map])
        size_map++;
    // if (!check_top_bottom(map, size_map))
    //     return (0);
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

int check_player_position(char **map)
{
    int  i;
    int j;
    
    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

static void	set_player_direction(t_data *data, int i, int j)
{
    if (data->map.map[i][j] == 'N')
        data->player.angle = 3 * M_PI / 2;
    else if (data->map.map[i][j] == 'S')
        data->player.angle = M_PI / 2;
    else if (data->map.map[i][j] == 'E')
        data->player.angle = 0;
    else if (data->map.map[i][j] == 'W')
        data->player.angle = M_PI;
    data->map.map[i][j] = '0';
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
                set_player_direction(data, i, j);
                return ;
            }
            j++;
        }
        i++;
    }
}

static int check_color_range(int color)
{
    int r;
    int g;
    int b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (0);
    return (1);
}

int check_config_data(t_data *data)
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
    if (!check_player_position(data->map.map))
    {
        fprintf(stderr, "Error: Player position not found\n");
        return (0);
    }
    return (1);
}

static int check_top_borders(char **map)
{
    int	i;

	i = 0;
	while(map[0][i])
	{
		if(map[0][i] == '1')
			i++;
		else if (map[0][i] =='0')
			return 0;
		else if(map[0][i] == '2')
		{
			if(map[1][i] == '0')
				return 0;
			else if (map[1][i] == '1')
				i++;
		}
	}
	return 1;
}

int check_bottom_borders(char **map, int height)
{
    int i;
    int buttom;
    
    buttom = height - 1;

    i = 0;
    while (map[buttom][i])
    {
        if(map[buttom][i] == '1')
            i++;
        else if (map[buttom][i] == '0')
            return 0;
        else if (map[buttom][i] == '2')
        {
            if(map[buttom -1 ][i] == '0')
                return 0;
            else if (map[buttom -1][i] == '1')
                i++;
        }
    }
    return 1;
}

int check_left_borders(char **map)
{
    int i;
    int left;

    i = 1;
    while (map[i])
    {
        left = 0;
        if(map[i][left] == '1')
            i++;
        else if (map[i][left] == '0')
            return 0;
        else if(map[i][left] == '2')    
        {
            if(map[i][left + 1] == '0')
                return 0;
            else if (map[i][left + 1] == '1')
                i++;
        }
    }
    return 1;
}

int check_right_borders(char **map)
{
    int right;
    int i;

    i = 1;
    while(map[i])
    {
        right = ft_strlen(map[i]) - 1;
        if(map[i][right] == '1')
            i++;
        else if (map[i][right] == '0')
            return 0;
        else if(map[i][right] == '2')    
        {
            if(map[i][right - 1] == '0')
                return 0;
            else if (map[i][right - 1] == '1')
                i++;
        }
    }   
    return (1); 
}


int	check_for_borders(char **map)
{
    int	height;

    height = 0;
    while (map[height])
        height++;
    if (!check_top_borders(map))
        return (0);
    if (!check_bottom_borders(map, height))
        return (0);
    if (!check_left_borders(map))
        return (0);
    if (!check_right_borders(map))
        return (0);
    return (1);
}


static void	inite_data(t_data *data)
{
    data->textures.ceil_color = -1;
    data->textures.floor_color = -1;
    data->color_index = 0;
    data->texture_index = 0;
    data->map.map = NULL;
    data->textures_path[0] = NULL;
    data->textures_path[1] = NULL;
    data->textures_path[2] = NULL;
    data->textures_path[3] = NULL;
}


static int	validate_args(int argc, char **argv, int *fd)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s map.cub\n", argv[0]);
        return (0);
    }
    if (!check_extension(argv[1]))
    {
        fprintf(stderr, "Error: File must have a .cub extension\n");
        return (0);
    }
    *fd = open(argv[1], O_RDONLY);
    if (*fd < 0)
    {
        perror("open");
        return (0);
    }
    return (1);
}


static void	cleanup(t_data *data, char **map)
{
    int	i;
    int	j;

    i = 0;
    while (map && map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
    j = 0;
    while (j < 4)
    {
        if (data->textures_path[j])
            free(data->textures_path[j]);
        j++;
    }
}




static void	print_map_info(t_data *data)
{
    printf("Map is valid.\n");
    printf("Player position: (%f, %f)  Angle: %f\n", 
        data->player.pos_x, data->player.pos_y, data->player.angle);
    printf("Map height: %d  width: %d\n", 
        data->map.height, data->map.width);
    printf("Ceiling color: %06X  Floor color: %06X\n", 
        data->textures.ceil_color, data->textures.floor_color);
    printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", 
        data->textures_path[0], data->textures_path[2], 
        data->textures_path[3], data->textures_path[1]);
}

int	main(int argc, char **argv)
{
    int		fd;
    char	**map;
    t_data	data;

    inite_data(&data);
    if (!validate_args(argc, argv, &fd))
        return (1);
    map = read_cub_file(fd, &data);
    if (map == NULL)
    {
        close(fd);
        return (1);
    }
    data.map.map = map;
    close(fd);
    if (!check_config_data(&data) || !check_for_borders(map))
    {
        fprintf(stderr, "Invalid map format\n");
        cleanup(&data, map);
        return (1);
    }
    set_player_data(&data);
    map_size(&data);
    print_map_info(&data);
    cleanup(&data, map);
    return (0);
}
