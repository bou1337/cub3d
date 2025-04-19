#include "cub3d.h"

int main(int argc, char *argv[])
{
    t_data *data;
    if (parsing_data(argc, argv, &data))
    {
        ft_fprintf("\033[1;31m❌ ERROR\n"
                   "\033[1;33m📋 Please ensure your file meets the following requirements:\033[0m\n"
                   "\033[36m • \033[0mContains valid \033[32mRGB color codes (0-255)\033[0m 🎨 for floor and ceiling\n"
                   "\033[36m • \033[0mIncludes all required \033[32mtexture paths\033[0m 🖼️ (NO, SO, WE, EA)\n"
                   "\033[36m • \033[0mMap is properly \033[32menclosed by walls\033[0m 🧱\n"
                   "\033[36m • \033[0mNo \033[32mduplicate configuration elements\033[0m ⚠️\n"
                   "\033[36m • \033[0mMap is positioned at the \033[32mend of the file\033[0m 📄\n"
                   "\033[36m • \033[0mOnly \033[32mone player starting position\033[0m 👤 is defined\n");
                   free_data(data) ;
        return (1);
    }

    return 1 ;
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