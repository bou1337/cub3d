#include "cub3d.h"

char *map_string = 
        "11111111111111111111\n"
        "11000000000000000011\n"
        "10000000000000000001\n"
        "10000000P00000000001\n"
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
            data->player.pos_x = 10 * SIZE;
            data->player.pos_y = 10 * SIZE; 
            data->player.fov = M_PI / 3;    
            data->player.move_forward = 0;  
            data->player.move_right = 0;
            data->player.turn_right = 0;
            data->map.height  = 20 ;
            data ->map.width = 20 ;
            data->textures_path[0] ="./textures/north3.xpm"  ;
            data->textures_path[1] ="./textures/south3.xpm"   ;
            data->textures_path[2] ="./textures/west3.xpm" ;
            data->textures_path[3] ="./textures/east3.xpm" ;
            data->rays = malloc(sizeof(t_ray) *1900);
            if (init_data(data) != 0)
            {
                printf("Error: Failed to initialize data\n");
                return (1);
            }
            
            // int  i  , j ;
            // i = 0  ;
            // j = 0 ;

            // while(i<20)
            // {
            //      j = 0 ;
            //      while(j<20)
            //      {
            //     printf("%c",data->map.map[i][j]) ;
            //     j++ ;
            //      }

            //      printf("\n") ;
            //      i++ ;
            // }
           // printf("hhhhhhhhh") ; 
         //   return 1 ;
            draw_map(data) ;
            mlx_hook(data->win, DestroyNotify, 0, ft_close, data);
	        mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_press, data);
         	mlx_hook(data->win, KeyRelease, KeyReleaseMask, ft_key_release, data);
	        //mlx_loop_hook(data->mlx, update_map, data);
            mlx_loop(data->mlx) ;
            return (0);
        }