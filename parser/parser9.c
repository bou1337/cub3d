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
    data->map.height = 0;
    data->map.width = 0;
    data->r = 0;
    data->g = 0;
    data->b = 0;
    data->textures_path[0] = NULL;
    data->textures_path[1] = NULL;
    data->textures_path[2] = NULL;
    data->textures_path[3] = NULL;
}
