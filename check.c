/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:46:27 by hfazaz            #+#    #+#             */
/*   Updated: 2025/04/12 21:26:02 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"  
#include <string.h>








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

 int	handle_no_texture(t_data *data, char *line)
{
    char	*path;

    path = extract_path(data, line);
    if (data->textures_path[0] != NULL)
    {
        fprintf(stderr, "Error: Duplicate texture path\n");
        free(path);
        return (0);
    }
    if (!path)
        return (0);
    data->textures_path[0] = path;
    return (1);
}

int	handle_so_texture(t_data *data, char *line)
{
    char	*path;

    path = extract_path(data, line);
    if (data->textures_path[2] != NULL)
    {
        fprintf(stderr, "Error: Duplicate texture path\n");
        free(path);
        return (0);
    }
    if (!path)
        return (0);
    data->textures_path[2] = path;
    return (1);
}

 int	handle_we_texture(t_data *data, char *line)
{
    char	*path;

    path = extract_path(data, line);
    if (data->textures_path[3] != NULL)
    {
        fprintf(stderr, "Error: Duplicate texture path\n");
        free(path);
        return (0);
    }
    if (!path)
        return (0);
    data->textures_path[3] = path;
    return (1);
}

 int	handle_ea_texture(t_data *data, char *line)
{
    char	*path;

    path = extract_path(data, line);
    if (data->textures_path[1] != NULL)
    {
        fprintf(stderr, "Error: Duplicate texture path\n");
        free(path);
        return (0);
    }
    if (!path)
        return (0);
    data->textures_path[1] = path;
    return (1);
}

 int	set_ceiling_color(t_data *data, char *line, int r, int g, int b)
{
    if (data->textures.ceil_color != -1)
    {
        fprintf(stderr, "Error: Duplicate ceiling color\n");
        free(line);
        return (0);
    }
    data->textures.ceil_color = (r << 16) | (g << 8) | b;
    return (1);
}

 int	set_floor_color(t_data *data, char *line, int r, int g, int b)
{
    if (data->textures.floor_color != -1)
    {
        fprintf(stderr, "Error: Duplicate floor color\n");
        free(line);
        return (0);
    }
    data->textures.floor_color = (r << 16) | (g << 8) | b;
    return (1);
}