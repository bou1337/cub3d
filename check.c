/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:46:27 by hfazaz            #+#    #+#             */
/*   Updated: 2025/04/08 11:36:42 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"  
#include <string.h>

int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_extension(const char *filename)
{
    const char  *dot;
    const char  *extension = ".cub";
    
    dot = NULL;
    while (*filename)
    {
        if (*filename == '.')
            dot = filename;
        filename++;
    }
    // printf("dot: %s\n", dot);
    if (!dot || dot[1] == '\0')
        return (0);
    
    if (ft_strcmp(dot, extension) == 0)
        return (1);
    
    return (0);
}

char *get_line(int fd)
{
    char *line;
    char *temp;
    int capacity = 128;
    int i = 0;
    char c;

    line = malloc(sizeof(char) * capacity);
    if (!line)
        return (NULL);

    while (read(fd, &c, 1) > 0)
    {
        if (c == '\n')
        {
            line[i] = '\0';
            return (line);
        }

        line[i++] = c;

        // Reallocate if we're approaching capacity
        if (i >= capacity - 1)
        {
            capacity *= 2;
            temp = malloc(sizeof(char) * capacity);
            if (!temp)
            {
                free(line);
                return (NULL);
            }
            memcpy(temp, line, i);
            free(line);
            line = temp;
        }
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

 char	*pad_line(char *line)
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
    long	num;
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
        // if (num > 0x7fffffff || (num * sign) < 0xffffffff)
        // {
        //     fprintf(stderr, "Error: Integer overflow\n");
        //     return (0);
        // }
        (*i)++;
    }
    return (sign * num);
}

 int	check_color_component(char *line, int *i, int *component)
{
    int	j;

    j = *i;
    *component = parse_int(line, i);
    if (*component < 0 || *component > 255 || *i == j)
        return (0);
    return (1);
}

int	parse_color(char *line, int *r, int *g, int *b)
{
    int	i;
    int	components_found;

    i = 1;
    components_found = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (!check_color_component(line, &i, r))
        return (0);
    components_found++;
    if (line[i++] != ',')
        return (0);
    if (!check_color_component(line, &i, g))
        return (0);
    components_found++;
    if (line[i++] != ',')
        return (0);
    if (!check_color_component(line, &i, b))
        return (0);
    components_found++;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (line[i] == '\0' && components_found == 3);
}

char *extract_path(t_data *data, char *line)
{
    int     i;
    int     j;
    char    *path;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if ((line[i] == 'N' && line[i + 1] == 'O') ||
        (line[i] == 'S' && line[i + 1] == 'O') ||
        (line[i] == 'W' && line[i + 1] == 'E') ||
        (line[i] == 'E' && line[i + 1] == 'A'))
    {
        i += 2;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '\0')
            return (NULL);
        j = i;
        while (line[j] && line[j] != ' ' && line[j] != '\t')
            j++;
        path = malloc(sizeof(char) * (j - i + 1));
        if (!path)
            return (NULL);
         j = 0;
        while (line[i] && line[i] != ' ' && line[i] != '\t')
        {
            path[j] = line[i];
            i++;
            j++;
        }
        path[j] = '\0';
        
        return (path);
    }
    return (NULL);
}

 int is_texture(t_data *data, char *line)
{
    int i;
    char *path;
    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == 'N' && line[i + 1] == 'O')
    {
        path = extract_path(data, line);
        if (path)
            data->textures_path[0] = path;
        else
            return (0);
    }
    else if (line[i] == 'S' && line[i + 1] == 'O')
    {
        path = extract_path(data, line);
        if (path)
            data->textures_path[2] = path;
        else
            return (0);
    }
    else if (line[i] == 'W' && line[i + 1] == 'E')
    {
        path = extract_path(data, line);
        if (path)
            data->textures_path[3] = path;
        else
            return (0);
    }
    else if (line[i] == 'E' && line[i + 1] == 'A')
    {
        path = extract_path(data, line);
        if (path)
            data->textures_path[1] = path;
        else
            return (0);
    }
    else
        return (0);
    
    return (1);
}

 int	handle_colors(t_data *data, char *line)
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

 int	handle_map_line(char *line, t_data *data, char **map, int *i)
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


int	process_config_line(char *line, t_data *data, char **map, int *i)
{
    if (line[0] == 'C' || line[0] == 'F')
        return (handle_colors(data, line));
    else if (is_texture(data, line))
    {
        data->texture_index = 1;
        return (1);
    }
    else if (is_map_line(line))
    {
        data->map_found = 1;
        handle_map_line(line, data, map, i);
    }
    
    else
    {
        free(line);
        return  (1);
    }
}

 int	read_config_lines(int fd, t_data *data, char **map, int *i)
{
    char	*line;

    while ((line = get_line(fd)))
    {
        if ((!process_config_line(line, data, map, i)  ))
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
            fprintf(stderr, "Error: Invalid structure\n");
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
                fprintf(stderr, "Error: Invalid content after map section\n");
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
    char	*line;

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


 int	allocate_map(char ***map, int map_length)
{
    *map = malloc(sizeof(char *) * (map_length + 1));
    if (!(*map))
        return (0);
    return (1);
}

int	process_map_data(int fd, t_data *data, char **map)
{
    int i;

    i = 0;
    if (!read_config_lines(fd, data, map, &i))
    {
        free(map);
        return (0);
    }
    if (!read_map_lines(fd, map, &i))
    {
        free(map);
        return (0);
    }
    
    if (i == 0)
    {
        fprintf(stderr, "Error: No valid map data found\n");
        free(map);
        return (0);
    }
    return (1);
}

char	**read_cub_file(int fd, t_data *data, char *filename)
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
    fd = open(filename, O_RDONLY);
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

int check_player_position(char **map)
{
    int  i;
    int  j;
    int  player_count;
    
    i = 0;
    player_count = 0;
    
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || 
                map[i][j] == 'E' || map[i][j] == 'W')
            {
                player_count++;
            }
            j++;
        }
        i++;
    }
    
    if (player_count == 0)
    {
        fprintf(stderr, "Error: No player position found\n");
        return (0);
    }
    else if (player_count > 1)
    {
        fprintf(stderr, "Error: Multiple player positions found\n");
        return (0);
    }
    
    return (1);
}

 void	set_player_direction(t_data *data, int i, int j)
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
 int check_color_range(int color)
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
int check_top_borders(char **map)
{
    int	i;

    i = 0;
    while (map[0][i])
    {
        if (map[0][i] == '1')
            i++;
        else if (map[0][i] == '0')
            return (0);
        else if (map[0][i] == '2')
        {
            if (map[1][i] == '0')
                return (0);
            else if (map[1][i] == '1')
                i++;
            else
                 i++ ;  
        }
        else
            return 0;
    }
    return (1);
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
            if(map[buttom - 1][i] == '0')
                return 0;
            else if (map[buttom - 1][i] == '1')
                i++;
            else
                 i++;
        }
        else
            return 0 ;  
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
            else
                i++;
        }
        else
            return 0; 
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
            else
                i++; 
        }
        else
            return  0;
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

 int	inite_data(t_data *data)
{
    data->textures.ceil_color = -1;
    data->textures.floor_color = -1;
    data->color_index = 0;
    data->texture_index = 0;
    data->map.map = NULL;
    data->map_found =  0;
    data->textures_path[0] = NULL;
    data->textures_path[1] = NULL;
    data->textures_path[2] = NULL;
    data->textures_path[3] = NULL;
}


 int	validate_args(int argc, char **argv, int *fd)
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


 void	cleanup(t_data *data, char **map)
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
int	check_map(t_data *data)
{
    int		i;
    int		j;
    int		len;
    char	**map;

    i = 1;
    len = data->map.height;
    map = data->map.map;
    while (i < len -1)
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0')
            {
                if ((map[i - 1][j] != '0' && map[i - 1][j] != '1') || 
                    (map[i + 1][j] != '0' && map[i + 1][j] != '1') || 
                    (map[i][j - 1] != '0' && map[i][j - 1] != '1') || 
                    (map[i][j + 1] != '0' && map[i][j + 1] != '1'))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

void ft_fprintf(const char *s)
{
    write(2,s,ft_strlen(s)) ;
}