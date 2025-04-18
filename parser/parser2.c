/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:41:44 by hfazaz            #+#    #+#             */
/*   Updated: 2025/04/18 16:41:45 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_int(const char *str, int *i)
{
	long	num;
	int		sign;

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
