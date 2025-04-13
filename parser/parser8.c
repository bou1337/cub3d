#include "../cub3d.h"

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