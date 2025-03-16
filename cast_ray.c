#include "cub3d.h"

int cast_rays(t_data *data)
{
    double	angle;
	int		i;

	angle = data->player.angle - (0.5 * data->player.fov);
	i = -1;
	while (data->rays && ++i < data->screen.width)
	{
		angle = normalize_angle(angle);
		data->rays[i].ray_angle = angle;
		data->rays[i].is_facing_up = angle >= PI;
		data->rays[i].is_facing_right = angle < (0.5 * PI) || angle > (1.5
				* PI);
		determine_ray_intersection(data, i);
		draw_ray(data, i);
		angle += data->player.fov / data->screen.width;
	}
	return (0);
}


int	determine_ray_intersection(t_data *data, int i)
{
	t_intersection	horz_intersection;
	t_intersection	vert_intersection;

	horz_intersection = find_horizontal_wall_intersection(data, i);
	vert_intersection = find_vertical_wall_intersection(data, i) ;
	if (horz_intersection.distance < vert_intersection.distance)
	{
		data->rays[i].distance = horz_intersection.distance;
		data->rays[i].hit_x = horz_intersection.x;
		data->rays[i].hit_y = horz_intersection.y;
		data->rays[i].hit_vertical = 0;
	}
	else
	{
		data->rays[i].distance = vert_intersection.distance;
		data->rays[i].hit_x = vert_intersection.x;
		data->rays[i].hit_y = vert_intersection.y;
		data->rays[i].hit_vertical = 1;
	}
	return (0);
}

