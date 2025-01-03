#ifndef CUB3D_H
#define CUB3D_H
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
#include <math.h>

# define X 600
# define Y 600
# define SIZE 30
# define SPEED  1  

typedef struct s_data {
    void    *mlx;          
    void    *win;          
    void    *img;          
    char    *img_data;     
    int     bpp;           
    int     line_len;      
    int     endian;        
    double     player_x;      
    double     player_y;      
    char    **map; 
    double  dirX;  
    double  dirY;          
    double  planeX;        
    double  planeY;
    double  teta ;             
} t_data;

void  my_pixel_put(t_data *img, int x, int y, int color);
void  draw_rect(t_data *data, int x, int y, int color);
void  draw_map(t_data *data);
int   key_code(int keycode, t_data *data);
char  **ft_split(const char *s, char c);
int update_game(t_data *data) ;
void draw_line(t_data *data , double x0 , double y0 , double x1, double y1) ;



#endif
