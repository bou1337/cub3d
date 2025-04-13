#include "../cub3d.h"

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
    if (!dot || dot[1] == '\0')
        return (0);
    
    if (ft_strcmp(dot, extension) == 0)
        return (1);
    
    return (0);
}

static char	*reallocate_line(char *line, int capacity, int i)
{
    char	*temp;
    int		j;

    temp = malloc(sizeof(char) * capacity);
    if (!temp)
    {
        free(line);
        return (NULL);
    }
    j = 0;
    while (j < i)
    {
        temp[j] = line[j];
        j++;
    }
    free(line);
    return (temp);
}

char	*get_line(int fd)
{
    char	*line;
    int		capacity;
    int		i;
    char	c;

    capacity = 128;
    i = 0;
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
        if (i >= capacity - 1)
        {
            capacity *= 2;
            line = reallocate_line(line, capacity, i);
            if (!line)
                return (NULL);
        }
    }
    return (handle_end_of_file(line, i));
}

char	*handle_end_of_file(char *line, int i)
{
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
    return (c == ' ' || c == '0' || c == '1' || c == '2'
        || c == 'N' || c == 'S' || c == 'W' || c == 'E');
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
