/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:05:41 by hfazaz            #+#    #+#             */
/*   Updated: 2025/04/19 15:05:42 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	validate_args(int argc, char **argv, int *fd)
{
	if (argc != 2)
	{
		return (0);
	}
	if (!check_extension(argv[1]))
	{
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
    int i;
    int j;

    i = 0;
    while (map && map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
    
    if (data)
        data->map.map = NULL;
        
    j = 0;
    while (j < 4)
    {
        if (data && data->textures_path[j])
        {
            free(data->textures_path[j]);
            data->textures_path[j] = NULL;
        }
        j++;
    }
}

void cleanup_all(t_data *data)
{
    free_textures(data);
    
    if (data->img.img)
        mlx_destroy_image(data->mlx, data->img.img);
    
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    
    for (int i = 0; i < 4; i++) {
        if (data->textures_path[i])
            free(data->textures_path[i]);
    }
    
    if (data->map.map) {
        for (int i = 0; data->map.map[i]; i++)
            free(data->map.map[i]);
        free(data->map.map);
    }
    
    if (data->rays)
        free(data->rays);
    
    if (data->mlx) {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    
  
    free(data);
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
	while (i < len - 1)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if ((map[i - 1][j] != '0' && map[i - 1][j] != '1') || (map[i
						+ 1][j] != '0' && map[i + 1][j] != '1') || (map[i][j
						- 1] != '0' && map[i][j - 1] != '1') || (map[i][j
						+ 1] != '0' && map[i][j + 1] != '1'))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_fprintf(const char *s)
{
	write(2, s, ft_strlen(s));
}

int	handle_no_texture(t_data *data, char *line)
{
    char *path;

    path = extract_path(data, line);
    if (data->textures_path[0] != NULL)
    {
        free(path);
        free(line); 
        return (0);
    }
    if (!path)
    {
        free(line);  
        return (0);
    }
    data->textures_path[0] = path;
    free(line); 
    return (1);
}