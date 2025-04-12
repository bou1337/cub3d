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