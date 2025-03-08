#ifndef CUB3D_H
#define CUB3D_H
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
#include <math.h>

# define X 30*20
# define Y 30*20
# define SIZE 8
# define SPEED  1  
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define FOV  M_PI/3 
#define RAYS_NUM 30*20
#define FLOOR_COLOR   0x654321  // Brown color for the floor
#define CEILING_COLOR 0x87CEEB  // Light blue color for the ceiling (sky)

typedef struct s_dir
{
    int down ;
    int  right  ;
}t_dir ;

typedef  struct s_rays 
{
    double y_intr;
    double x_intr;
    double dx ;
    double  dy ;
    double x_wall_h ;
    double y_wall_h ;
    double x_wall_v ;
    double y_wall_v;
    double dis_h ;
    double dis_v ;
    double x_wall ;
    double y_wall ;
    double dis ;
    int down ;
    int right ;
}t_rays ;
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
    char		*textures_path[4];
	// t_data		*texture[4];      
    char    **map; 
    double  dirX;  
    double  dirY;          
    double  planeX;        
    double  planeY;
    double  teta ;
    t_rays  *ray;
} t_data;

typedef struct s_textures
{
	t_data		north;
	t_data		south;
	t_data		east;
	t_data		west;
	int			floor_color;
	int			ceil_color;
}				t_textures;


int   my_pixel_put(t_data *img, int x, int y, int color);
void  draw_rect(t_data *data, int x, int y, int color);
void  draw_map(t_data *data);
int   key_code(int keycode, t_data *data);
char  **ft_split(const char *s, char c);
int update_game(t_data *data) ;
void draw_line(t_data *data , double x0 , double y0 , double x1, double y1) ;
void   draw_rays(t_data  * data)  ; 
void   normalize_angl(double *angl) ;
void horizontal_intr(t_data *data, t_rays *ray, double angl) ;
int check_wall(t_data *data, double x, double y) ;
void dir_r(t_rays *ray, double angl) ;
void vertical_intr(t_data *data, t_rays *ray, double angl) ;
void draw_vertical_line(t_data *data, int x, int start, int end) ;
void draw_wall(t_data *data) ;
void draw_vertical_line_color(t_data *data, int x, int start, int end, int color) ;
#endif
