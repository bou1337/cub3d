#include "cub3d.h"

void free_data(t_data *data)
{
    int i;
    
    if (!data)
        return;
    
    // Free rays array
    if (data->rays)
    {
        free(data->rays);
        data->rays = NULL;
    }
    
    // Free map data
    if (data->map.map)
    {
        i = 0;
        while (data->map.map[i])
        {
            free(data->map.map[i]);
            data->map.map[i] = NULL;
            i++;
        }
        free(data->map.map);
        data->map.map = NULL;
    }
    
    // Free texture paths
    for (int j = 0; j < 4; j++)
    {
        if (data->textures_path[j])
        {
            free(data->textures_path[j]);
            data->textures_path[j] = NULL;
        }
    }
    
    // Free the data structure itself
    free(data);
}
