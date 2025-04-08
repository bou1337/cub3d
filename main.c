#include "cub3d.h"


#include "cub3d.h"




        int main(int argc, char *argv[])
        {
            int		fd;
            char	**map;
            t_data *data;
             
            if(inite_data(data)) 
              return 1  ;
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
        
          
             if (init_data(data))
                return (1);
            data->map.redraw = 1;
            draw_map(data);
            mlx_hook(data->win, DestroyNotify, 0, ft_close, data);
            mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_press, data);
            mlx_hook(data->win, KeyRelease, KeyReleaseMask, ft_key_release, data);
            mlx_loop_hook(data->mlx, update_map, data);
            mlx_loop(data->mlx);
            return (0);
        }