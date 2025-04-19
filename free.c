
#include "cub3d.h"


void free_data(t_data *data)
{
    if (data)
    {
        if (data->rays)
        {
            free(data->rays);
            data->rays = NULL;
        }
        free(data);
        data = NULL;  
    }
}
