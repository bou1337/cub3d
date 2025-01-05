#ifndef CUB3D_H
#define CUB3D_H
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
#include <math.h>

# define X 30*20
# define Y 30*19
# define SIZE 30
# define SPEED  1  
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define FOV  M_PI/3 
#define RAYS_NUM 30*20  
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
void   draw_rays(t_data  * data)  ; 

#endif
