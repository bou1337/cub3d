#include "cub3d.h"

int	update_player(t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_angle;

	if (data->player.move_forward != 0)
	{
		move_forward_backward(data, &new_x, &new_y);
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	if (data->player.move_right != 0)
	{
		move_right_left(data, &new_x, &new_y);
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	if (data->player.turn_right != 0)
	{
		new_angle = turn_right_left(data, data->player.turn_right == 1);
		data->player.angle = new_angle;
	}
	return (0);
}


int move_forward_backward(t_data *data, double *new_x, double *new_y)
{
    double move_speed = 3.0; 
    
    if (data->player.move_forward == 1)
    {
        *new_x = data->player.pos_x + cos(data->player.angle) * move_speed;
        *new_y = data->player.pos_y + sin(data->player.angle) * move_speed;
    }
    else if (data->player.move_forward == -1)
    {
        *new_x = data->player.pos_x - cos(data->player.angle) * move_speed;
        *new_y = data->player.pos_y - sin(data->player.angle) * move_speed;
    }
    
    if (!player_inside_map(data, *new_x, *new_y))
    {
        *new_x = data->player.pos_x;
        *new_y = data->player.pos_y;
    }
    return (0);
}

int move_right_left(t_data *data, double *new_x, double *new_y)
{
    double move_speed = 3.0; 
    
    if (data->player.move_right == 1)
    {
        *new_x = data->player.pos_x + cos(data->player.angle + (M_PI/2)) * move_speed;
        *new_y = data->player.pos_y + sin(data->player.angle + (M_PI/2)) * move_speed;
    }
    else if (data->player.move_right == -1)
    {
        *new_x = data->player.pos_x + cos(data->player.angle - (M_PI/2)) * move_speed;
        *new_y = data->player.pos_y + sin(data->player.angle - (M_PI/2)) * move_speed;
    }

    if (!player_inside_map(data, *new_x, *new_y))
    {
        *new_x = data->player.pos_x;
        *new_y = data->player.pos_y;
    }
    return (0);
}

double turn_right_left(t_data *data, int turn_right)
{
    double new_angle;
    new_angle = data->player.angle;
    if (turn_right)
        new_angle += 0.1; 
    else
        new_angle -= 0.1;
    new_angle = normalize_angle(new_angle); // Normalize the angle
    return (new_angle);
}
