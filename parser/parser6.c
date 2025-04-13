#include "../cub3d.h"

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
