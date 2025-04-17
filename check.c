/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:46:27 by hfazaz            #+#    #+#             */
/*   Updated: 2025/04/17 17:40:29 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"  
#include <string.h>


int	handle_so_texture(t_data *data, char *line)
{
    char	*path;

    path = extract_path(data, line);
    if (data->textures_path[2] != NULL)
    {
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
        free(path);
        return (0);
    }
    if (!path)
        return (0);
    data->textures_path[1] = path;
    return (1);
}

 int	set_ceiling_color(t_data *data, char *line)
{
    if (data->textures.ceil_color != -1)
    {
        free(line);
        return (0);
    }
    data->textures.ceil_color = (data-> r << 16) | (data -> g << 8) | data->b;
    return (1);
}

 int	set_floor_color(t_data *data, char *line)
{
    if (data->textures.floor_color != -1)
    {
        free(line);
        return (0);
    }
    data->textures.floor_color = (data->r << 16) | (data->g << 8) | data->b;
    return (1);
}