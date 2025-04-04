#include "cub3d.h"

char *map_string = 
        "11111111111111111111\n"
        "11000000000000000011\n"
        "12200000000000000001\n"
        "10000000000000000001\n"
        "1111111111111111111\n"
        "12222222222222222211\n"
        "11111111111112222101\n"
        "10000000000012222101\n"
        "10000000200000000001\n"
        "10000000000000111111\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000001000000001\n"
        "111111111111110000011\n"
        "12222222222100000001\n"
        "11111111111100000001\n"
        "11000000000000000011\n"
        "11000000000000000011\n"
        "11111111111111111111\n";

        int main(void)
        {
            t_data *data;
            data = malloc(sizeof(t_data));
            if (!data)
            {
                printf("Error: Failed to allocate memory for data\n");
                return (1);
            }
        
            ft_memset(data, 0, sizeof(t_data)); 
            data->map.map = ft_split(map_string, '\n');
            if (!data->map.map)
            {
                printf("Error: Failed to split map string\n");
                return (1);
            }
            
            data->player.pos_x = 10 ;
            data->player.pos_y = 10 ; 
            data->player.angle = M_PI ; // Initialize player angle (facing north)   
            data->player.move_forward = 0;  
            data->player.move_right = 0;
            data->player.turn_right = 0;
            data->map.height = 20;
            data->map.width = 20;
            data->textures.floor_color = 8543821 ;
            data->textures.ceil_color =0x87CEEB; 
            data->textures_path[0] ="./textures/1.xpm";
            data->textures_path[1] ="./textures/2.xpm";
            data->textures_path[2] ="./textures/3.xpm";
            data->textures_path[3] ="./textures/4.xpm";
            data->screen.height = 1000;
	        data->screen.width = 1900;
	        data->screen.size = 8;
            data->player.move_forward = 0;
	        data->player.move_right = 0;
	        data->player.turn_right = 0;
	        data->player.fov = M_PI/6;
	        data->player.move_speed = 1;
	        data->player.turn_speed = 1.4;
	        data->player.pos_x *= data->screen.size;
	        data->player.pos_y *= data->screen.size;
            
            data->rays = malloc(sizeof(t_ray) * 1900);
            if (!data->rays)
            {
                printf("Error: Failed to allocate memory for rays\n");
                return (1);
            }
        
            if (init_data(data) != 0)
            {
                printf("Error: Failed to initialize data\n");
                return (1);
            }
            data->map.redraw = 1;
            draw_map(data);
            mlx_hook(data->win, DestroyNotify, 0, ft_close, data);
            mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_press, data);
            mlx_hook(data->win, KeyRelease, KeyReleaseMask, ft_key_release, data);
            mlx_loop_hook(data->mlx, update_map, data);
            mlx_loop(data->mlx);
            return (0);
        }