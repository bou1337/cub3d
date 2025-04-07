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

        int main(int argc, char *argv[])
        {
            int		fd;
            char	**map;
            t_data *data;
            data = malloc(sizeof(t_data));
            if (!data)
            {
                printf("Error: Failed to allocate memory for data\n");
                return (1);
            }
            inite_data1(data) ;
            if (!validate_args(argc, argv, &fd))
            return (1);
            map = read_cub_file(fd, data, argv[1]);
           if (map == NULL)
           {
           close(fd);
            return (1);
            }
            data->map.map = map;
            close(fd);

          if (!check_config_data(data) || !check_for_borders(map))
          {
        fprintf(stderr, "Invalid map format\n");
        cleanup(data, map);
        return (1);
        }
        set_player_data(data);
        map_size(data);
            init_data(data);
             // Initialize player angle (facing north)   
            data->player.move_forward = 0;  
            data->player.move_right = 0;
            data->player.turn_right = 0;    
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