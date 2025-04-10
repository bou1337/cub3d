#include "cub3d.h"

        int main(int argc, char *argv[])
        {
            t_data *data;
          if (!parsing_data(argc, argv, &data))
              printf("valid map \n");
            // data->map.redraw = 1;
            // draw_map(data);
            // mlx_hook(data->win, DestroyNotify, 0, ft_close, data);
            // mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_press, data);
            // mlx_hook(data->win, KeyRelease, KeyReleaseMask, ft_key_release, data);
            // mlx_loop_hook(data->mlx, update_map, data);
            // mlx_loop(data->mlx);
            return (0);
        }