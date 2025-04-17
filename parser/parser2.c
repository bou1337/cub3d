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
