#include "../cub3d.h"

int	parse_int(const char *str, int *i)
{
    long	num;
    int	sign;

    num = 0;
    sign = 1;
    while (str[*i] == ' ' || str[*i] == '\t')
        (*i)++;
    if (str[*i] == '-')
    {
        sign = -1;
        (*i)++;
    }
    while (str[*i] >= '0' && str[*i] <= '9')
    {
        num = num * 10 + (str[*i] - '0');
        // if (num > 0x7fffffff || (num * sign) < 0xffffffff)
        // {
        //     fprintf(stderr, "Error: Integer overflow\n");
        //     return (0);
        // }
        (*i)++;
    }
    return (sign * num);
}

//  int	check_color_component(char *line, int *i, int *component)
// {
//     int	j;

//     j = *i;
//     *component = parse_int(line, i);
//     if (*component < 0 || *component > 255 || *i == j)
//         return (0);
//     return (1);
// }

// int	parse_color(char *line, t_data *data)
// {
//     int	i;
//     int	components_found;
    
//     i = 1;
//     components_found = 0;
//     while (line[i] == ' ' || line[i] == '\t')
//         i++;
//     if (!check_color_component(line, &i, &data->r))
//         return (0);
//     components_found++;
//     if (line[i++] != ',')
//         return (0);
//     if (!check_color_component(line, &i, &data->g))
//         return (0);
//     components_found++;
//     if (line[i++] != ',')
//         return (0);
//     if (!check_color_component(line, &i, &data->b))
//         return (0);
//     components_found++;
//     while (line[i] == ' ' || line[i] == '\t')
//         i++;
//     return (line[i] == '\0' && components_found == 3);
// }

// int	is_direction_identifier(char c1, char c2)
// {
//     return ((c1 == 'N' && c2 == 'O') || (c1 == 'S' && c2 == 'O') ||
//         (c1 == 'W' && c2 == 'E') || (c1 == 'E' && c2 == 'A'));
// }

// char	*allocate_path(char *line, int start)
// {
//     int		j;
//     int		len;
//     char	*path;

//     j = start;
//     while (line[j] && line[j] != ' ' && line[j] != '\t')
//         j++;
//     len = j - start;
//     path = malloc(sizeof(char) * (len + 1));
//     if (!path)
//         return (NULL);
//     return (path);
// }
