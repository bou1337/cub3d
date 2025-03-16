#include "cub3d.h"

char *map_string = 
        "11111111111111111111\n"
        "11000000000000000011\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000011111111111\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000111111\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000000000000001\n"
        "10000000001000000001\n"
        "10000000000111111111\n"
        "10000000000000000001\n"
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
            data->player.angle = M_PI / 2; // Initialize player angle (facing north)
            data->player.fov = M_PI / 3;    
            data->player.move_forward = 0;  
            data->player.move_right = 0;
            data->player.turn_right = 0;
            data->map.height = 20;
            data->map.width = 20;
            data->textures.floor_color = 8543821 ;
            data->textures.ceil_color =0x87CEEB; 
            data->textures_path[0] ="./textures/north3.xpm";
            data->textures_path[1] ="./textures/south3.xpm";
            data->textures_path[2] ="./textures/west3.xpm";
            data->textures_path[3] ="./textures/east3.xpm";
            data->screen.height = 1000;
	        data->screen.width = 1900;
	        data->screen.obj_size = 8;
            data->player.move_forward = 0;
	        data->player.move_right = 0;
	        data->player.turn_right = 0;
	        data->player.fov = 60 * (PI / 180);
	        data->player.move_speed = 0.9;
	        data->player.turn_speed = 2.5;
	        data->player.pos_x *= data->screen.obj_size;
	        data->player.pos_y *= data->screen.obj_size;
            
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