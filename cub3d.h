
#ifndef CUB3D_H
#define CUB3D_H
# include <X11/X.h>
# include <X11/keysym.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#define X 600
#define Y 600
#define SIZE 30 
#define speed 1 ;

typedef struct s_data {
    void    *mlx;          // MinilibX instance
    void    *win;          // Window pointer
    void    *img;          // Image pointer
    char    *img_data;     // Image buffer (data address)
    int     bpp;           // Bits per pixel
    int     line_len;      // Length of each image line (in bytes)
    int     endian;        // Endianness
    int     player_x;      // Player's x position
    int     player_y;      // Player's y position
    char    **map ;
} t_data;

void  my_pixel_put(t_data *img, int x, int y, int color) ;
void  draw_rect(t_data *data, int x , int y, int color) ;
void  draw_map(t_data *data) ;
int key_code(int keycode, t_data *data) ;
char **ft_split(const char *s, char c) ;

#endif