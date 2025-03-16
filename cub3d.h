#ifndef CUB3D_H
#define  CUB3D_H


#include <mlx.h>
#include <stdio.h>
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265358   
# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_img
{
    void *img ;
    void *addr ;
    int bpp ;
    int line ;
    int endian ;
	int  w ;
	int h ;
}t_img ;
typedef struct s_ray
{
	double		ray_angle;
	int			is_facing_up;
	int			is_facing_right;
	double		hit_x;
	double		hit_y;
	double		wall_h;
	double		r_wall_h;
	double		distance;
	double		top_y;
	double		bottom_y;
	double		r_top_y;
	double		r_bottom_y;
	int			hit_vertical;
}t_ray;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;

	int			player_dir;

	double		angle;
	double		fov;
	int			move_forward;
	int			move_right;
	int			turn_right;
	double		move_speed;
	double		turn_speed;
}t_player ;


typedef struct s_textures
{
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	int			floor_color;
	int			ceil_color;
}t_textures;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	int			redraw;

}t_map;


typedef struct s_intr
{
	double		distance;
	double		x;
	double		y;
}				t_intr;



typedef struct s_intersection
{
	double		distance;
	double		x;
	double		y;
}				t_intersection;
typedef struct s_screen
{
	double		width;
	double		height;
	double		obj_size;
}				t_screen;


typedef struct s_step
{
	double		x;
	double		y;
}				t_step;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		*textures_path[4];
	t_img		img;
	t_img		*texture[4];
	t_map		map;
	t_screen    screen ;
	t_textures	textures;
	t_player	player;
	t_ray		*rays;

}t_data;

int  init_data(t_data *data)  ;

t_intersection	find_horizontal_wall_intersection(t_data *data, int i)     ;

t_intersection	find_vertical_wall_intersection(t_data *data, int i)   ;

int	inter_check(t_data *data, int idx, double *inter, int is_horizon)  ;
int	pixel_in_screen(t_data *data, double x, double y)  ;
int	player_inside_map(t_data *data, double player_x, double player_y)  ;
int cast_rays(t_data *data)  ;
int	determine_ray_intersection(t_data *data, int i)  ;
int	update_map(t_data *data)  ;
int	draw_map(t_data *data) ; 
int	draw_ray(t_data *data, int x) ;
int	draw_column(t_data *data, int x) ;
int	ft_close(t_data *data) ;
int	free_textures(t_data *data) ;
int	valid_key(int key, t_data *data) ;
int	ft_key_press(int key, t_data *data) ;
int	ft_key_release(int key, t_data *data) ;
int	update_player(t_data *data) ; 
int	move_forward_backward(t_data *data, double *new_x, double *new_y)  ;
int	move_right_left(t_data *data, double *new_x, double *new_y) ;
double	turn_right_left(t_data *data, int turn_right)  ;
char **ft_split(const char *s, char c) ;
double	normalize_angle(double angle_tofix)  ;
void	*ft_memset(void *s, int c, size_t n)  ;
int	put_color_to_pixel(t_data *data, int x, int y, int col) ; 
int	put_pixel_to_pixel(t_data *data, t_img *img, int x, int y) ;
int	pixel_in_screen(t_data *data, double x, double y) ;
t_img	*get_img(t_data *data, int i) ; 
double	get_distance_between(double x1, double y1, double x2, double y2) ;
int	pixel_inside_map(t_data *data, double x, double y) ;
int	ft_strlen(const char *s) ;

#endif
