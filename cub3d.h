#ifndef CUB3D_H
#define  CUB3D_H

#include <stdio.h>
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
# include <unistd.h>
#define  SIZE   8    
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
	int			*map_line_len;
	int			map_start;
	int			fd;
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

typedef struct s_incr
{
	double		x;
	double		y;
}				t_incr;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**lines;
	int			textures_found;
	int			colors_found;
	char		*textures_path[4];
	char		*trimmed;
	int		texture_index;
	int 		map_index;
	int color_index;
	t_img		img;
	t_img		*texture[4];
	t_map		map;
	t_textures	textures;
	t_player	player;
	t_ray		*rays;

}t_data;

int  init_data(t_data *data) ;
char **ft_split(const char *s, char c) ;
void normalize_angl(double *angl) ;
void	*ft_memset(void *s, int c, size_t n) ;
int cast_rays(t_data *data) ;
t_intr	find_horizontal_wall_intersection(t_data *data, int i) ;
t_intr	find_vertical_wall_intersection(t_data *data, int i) ;

#endif