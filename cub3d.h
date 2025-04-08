#ifndef CUB3D_H
#define  CUB3D_H


#include <mlx.h>
#include <stdio.h>
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
 // For fprintf

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

typedef struct s_screen
{
	double		width;
	double		height;
	double		size;
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
	int map_found  ;
	int color_index ;
	int texture_index ;
}t_data;

void draw_rect(t_data *data, int x, int y, int color) ;
void draw_mapp(t_data *data) ;
void draw_line(t_data *data , double x0 , double y0 , double x1, double y1);
int  init_data(t_data *data)  ;
void  mini_map(t_data *data) ;
t_intr	find_horizontal_wall_intersection(t_data *data, int i)     ;
t_intr	find_vertical_wall_intersection(t_data *data, int i)   ;
int	inter_check(t_data *data, int idx, double *inter, int is_horizon)  ;
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
t_img	*get_img(t_data *data, int i) ; 
double	get_distance_between(double x1, double y1, double x2, double y2) ;
int	pixel_inside_map(t_data *data, double x, double y) ;
int	ft_strlen(const char *s) ;
int ft_strcmp(const char *s1, const char *s2) ;
int	check_extension(const char *filename) ;
char	*get_line(int fd) ;
int	is_valid_map_char(char c) ;
int	is_map_line(char *line) ;
int	parse_int(const char *str, int *i) ;
int	parse_color(char *line, int *r, int *g, int *b)  ;
char *extract_path(t_data *data, char *line) ;
int	map_len(int fd)  ;
char	**read_cub_file(int fd, t_data *data, char *filename) ;
void map_size(t_data *data) ;
int check_player_position(char **map) ;
void	set_player_data(t_data *data) ;
int check_config_data(t_data *data) ;
int check_bottom_borders(char **map, int height) ;
int check_left_borders(char **map) ;
int check_right_borders(char **map) ;
int	check_for_borders(char **map) ;
char	*pad_line(char *line) ;
int	check_color_component(char *line, int *i, int *component) ;
int is_texture(t_data *data, char *line) ;

int	handle_colors(t_data *data, char *line) ;
int	handle_map_line(char *line, t_data *data, char **map, int *i) ;
int	process_config_line(char *line, t_data *data, char **map, int *i) ; 
int	read_config_lines(int fd, t_data *data, char **map, int *i)  ;
int	check_empty_line(char *line) ;
int	read_remaining_lines(int fd) ;
int	read_map_lines(int fd, char **map, int *i)  ;
int	allocate_map(char ***map, int map_length) ;

int	process_map_data(int fd, t_data *data, char **map) ; 
void	set_player_direction(t_data *data, int i, int j)  ;
int check_color_range(int color) ;
int check_top_borders(char **map) ;
void	inite_data1(t_data *data) ;
int	validate_args(int argc, char **argv, int *fd) ;
void	cleanup(t_data *data, char **map)  ;
void Set_player_movement_state(t_data *data) ;
int allocation(t_data *data)  ;

#endif
