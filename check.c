/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:46:27 by hfazaz            #+#    #+#             */
/*   Updated: 2025/03/08 22:56:50 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char *get_line(int fd)
{
    char *line;
    int i;

    i = 0;
    line = malloc(sizeof(char) * 2147483647);
    if (!line)
        return NULL;
    while (read(fd, &line[i], 1))
    {
        if (line[i] == '\n')
        {
            line[i] = '\0';
            printf("----------->  %s\n", line);
            return line;
        }
        i++;
    }
    if (i > 0)
    {
        line[i] = '\0';
        printf("----------->  %s\n", line);
        return line;
    }
    free(line);
    return NULL;  
}

/* Check if a given line contains only allowed map characters.
   Allowed characters are: space, '0', '1', '2', 'N','S','W','E'
*/
int is_map_line(char *line)
{
    int i = 0;
    if (!line || !line[0])
        return 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '0' && line[i] != '1' &&
            line[i] != '2' && line[i] != 'N' && line[i] != 'S' &&
            line[i] != 'W' && line[i] != 'E')
            return 0;
        i++;
    }
    return 1;
}

/*
 * After reading the raw map, pad every line to max_len.
 */
char **pad_map(char **map)
{
    int i, j;
    int max_len = 0;
    int row = 0;
    char **padded;
    
    while (map[row])
    {
        int len = ft_strlen(map[row]);
        if (len > max_len)
            max_len = len;
        row++;
    }
    padded = malloc(sizeof(char *) * (row + 1));
    if (!padded)
        return NULL;
    for (i = 0; i < row; i++)
    {
        padded[i] = malloc(sizeof(char) * (max_len + 1));
        if (!padded[i])
            return NULL;
        j = 0;
        while (map[i][j])
        {
            padded[i][j] = map[i][j];
            j++;
        }
        // pad the rest with spaces
        while (j < max_len)
            padded[i][j++] = ' ';
        padded[i][j] = '\0';
    }
    padded[i] = NULL;
    return padded;
}

char **save_map(int fd)
{
    char *line;
    char **map;
    int i;

    i = 0;
    map = malloc(sizeof(char *) * 2147483647);
    if (!map)
        return NULL;
    // Skip configuration or non-map lines until a valid map line is found.
    while ((line = get_line(fd)))
    {
        if (is_map_line(line))
            break;
        free(line);
    }
    if (!line)
    {
        free(map);
        return NULL;
    }
    map[i++] = line;
    while ((line = get_line(fd)))
    {
        if (!is_map_line(line))
        {
            free(line);
            break;
        }
        map[i++] = line;
    }
    map[i] = NULL;
    // Pad the map so all lines have the same length.
    return pad_map(map);
}

int check_top_bottom(char **map, int size)
{
    int i = 0;
    
    while (map[0][i])
    {
        if (map[0][i] != '1')
            return 0;
        i++;
    }
    i = 0;
    while (map[size - 1][i])
    {
        if (map[size - 1][i] != '1')
            return 0;
        i++;
    }
    return 1;
}

int check_borders(char **map)
{
    int i;
    int len;
    int size_map = 0;

    while (map[size_map])
        size_map++;
    
    if (!check_top_bottom(map, size_map))
        return 0;
    
    for (i = 1; i < size_map - 1; i++)
    {
        len = ft_strlen(map[i]);
        if (map[i][0] != '1' || map[i][len - 1] != '1')
            return 0;
    }
    return 1;
}

int valid_map(char **map)
{
    if (check_borders(map))
        return 1;
    return 0;
}

int main(int argc, char **argv)
{
    int fd;
    char **map;
    t_data data;
    int i;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s map.cub\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    map = save_map(fd);
    data.map = map;
    close(fd);
    if (!map)
    {
        fprintf(stderr, "Failed to load map\n");
        return 1;
    }
    if (!valid_map(map))
    {
        fprintf(stderr, "Invalid map format\n");
        return 1;
    }
    printf("Map is valid.\n");

    i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        free(map[i]);
        i++;
    }
    free(map);
    return 0;
}