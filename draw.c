#include "cub3d.h"

int  my_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;
     if (x < 0 || y >= 20*30 || y< 0 || y >= 20*30)
        return 0; 
    dst = img->img_data + y * img->line_len + (x * (img->bpp / 8));
    *(unsigned int *)dst = color;
    return 0 ;
}

void draw_rect(t_data *data, int x, int y, int color)
{
    int start_x = x * SIZE;
    int start_y = y * SIZE;
    int end_x = start_x + SIZE;
    int end_y = start_y + SIZE;
    int i ; 
    int j ;
    i = start_x ;
    
    while(i<end_x)
    {
         j= start_y ;
        while( j < end_y)
        {        
            my_pixel_put(data, i, j, color);
            j++ ;
        }
        i++ ;
    }
}

void draw_map(t_data *data)
{
    int i  = 0 ;
    int j  = 0  ;
    while(data->map[i])
    {       
        j = 0 ;
        while(data->map[i][j])
        {
            if (data->map[i][j] == '1')
                draw_rect(data, j, i, 0x0000FF); 
            else
                draw_rect(data, j, i, 0xFFFFFF);
                j++ ; 
        }
        i++ ;
}


 my_pixel_put(data, data->player_x, data->player_y, 0xFF0000) ;
 my_pixel_put(data, data->player_x, data->player_y+1, 0xFF0000) ;
 my_pixel_put(data, data->player_x+1, data->player_y, 0xFF0000) ; 
 my_pixel_put(data, data->player_x-1, data->player_y, 0xFF0000) ;
 my_pixel_put(data, data->player_x, data->player_y-1, 0xFF0000) ;
 draw_rays(data) ; 
 //draw_line(data,data->player_x , data->player_y , data->player_x +70*cos(data->teta), data->player_y+70*sin(data->teta)) ;
 //draw_line(data,data->player_x , data->player_y , data->player_x +70*cos(data->teta+FOV/2), data->player_y+70*sin(data->teta+FOV/2)) ;
 //draw_line(data,data->player_x , data->player_y , data->player_x +70*cos(data->teta-FOV/2), data->player_y+70*sin(data->teta-FOV/2)) ;
 // draw_line(data,data->player_x , data->player_y , data->player_x +40*cos(data->teta+FOV/3), data->player_y+40*sin(data->teta+FOV/3)) ;
 //  draw_line(data,data->player_x , data->player_y , data->player_x +40*cos(data->teta+FOV/RAYS_NUM), data->player_y+40*sin(data->teta+FOV/RAYS_NUM)) ;
   // draw_line(data,data->player_x , data->player_y , data->player_x +40*cos(data->teta+FOV/RAYS_NUM), data->player_y+40*sin(data->teta+FOV/RAYS_NUM)) ;
     //draw_line(data,data->player_x , data->player_y , data->player_x +40*cos(data->teta-FOV/RAYS_NUM), data->player_y+40*sin(data->teta-FOV/RAYS_NUM)) ;
 
 }
void draw_rays(t_data *data) {
    t_rays ray;
    int num_rays = 20*30; 
    double fov = M_PI / 3; 
    double angle_step = fov / num_rays;
    double angl_r = data->teta - fov / 2;
    int  i  = 0 ;
    while(i<num_rays) {
        normalize_angl(&angl_r);
        horizontal_intr(data, &ray, angl_r);
        vertical_intr(data, &ray, angl_r);
        if (ray.dis_h < ray.dis_v)
        {
            data->ray[i].x_wall=ray.x_wall_h ;
            data->ray[i].y_wall = ray.y_wall_h ;
            data->ray[i].dis=ray.dis_h ;
        }
     //       draw_line(data, data->player_x, data->player_y, ray.x_wall_h, ray.y_wall_h);
        else
        {

             data->ray[i].x_wall=ray.x_wall_v ;
            data->ray[i].y_wall = ray.y_wall_v ;
            data->ray[i].dis=ray.dis_v ;
        }
       //     draw_line(data, data->player_x, data->player_y, ray.x_wall_v, ray.y_wall_v);
       

        draw_line(data, data->player_x, data->player_y, data->ray[i].x_wall,data->ray[i].y_wall);
        angl_r += angle_step;
        i++ ;
    }
}void horizontal_intr(t_data *data, t_rays *ray, double angl) {
    dir_r(ray, angl);
    ray->y_intr = floor(data->player_y / SIZE) * SIZE;
    if (ray->down) 
        ray->y_intr += SIZE; 

    ray->x_intr = data->player_x + (ray->y_intr - data->player_y) / tan(angl);

    ray->dy = ray->down ? SIZE : -SIZE; 
    ray->dx = ray->dy / tan(angl);      
    if (angl == 0 || angl == M_PI) {
        ray->dy = ray->down ? SIZE : -SIZE;
        ray->dx = 0; 
    }
    ray->x_wall_h = ray->x_intr;
    ray->y_wall_h = ray->y_intr;
    while (!check_wall(data, ray->x_wall_h, ray->y_wall_h - (ray->down ? 0 : 1))) {
        ray->x_wall_h += ray->dx;
        ray->y_wall_h += ray->dy; 
        if (ray->x_wall_h < 0 || ray->x_wall_h >= 20* SIZE ||
            ray->y_wall_h < 0 || ray->y_wall_h >=20 * SIZE)
            break;
    }
    ray->dis_h = sqrt(pow(ray->x_wall_h - data->player_x, 2) +
                      pow(ray->y_wall_h - data->player_y, 2));
}

void vertical_intr(t_data *data, t_rays *ray, double angl) {
    dir_r(ray, angl);
    ray->x_intr = floor(data->player_x / SIZE) * SIZE;
    if (ray->right) 
        ray->x_intr += SIZE; 

    ray->y_intr = data->player_y + (ray->x_intr - data->player_x) * tan(angl);
    ray->dx = ray->right ? SIZE : -SIZE; 
    ray->dy = ray->dx * tan(angl);     

    if (angl == M_PI / 2 || angl == 3 * M_PI / 2) {
        ray->dx = ray->right ? SIZE : -SIZE;
        ray->dy = 0;
    }
    ray->x_wall_v = ray->x_intr;
    ray->y_wall_v = ray->y_intr;
    while (!check_wall(data, ray->x_wall_v - (ray->right ? 0 : 1), ray->y_wall_v)) {
        ray->x_wall_v += ray->dx; 
        ray->y_wall_v += ray->dy; 
        if (ray->x_wall_v < 0 || ray->x_wall_v >= 20 * SIZE ||
            ray->y_wall_v < 0 || ray->y_wall_v >= 20 * SIZE)
            break;
    }
    ray->dis_v = sqrt(pow(ray->x_wall_v - data->player_x, 2) +
                      pow(ray->y_wall_v - data->player_y, 2));
}



int check_wall(t_data *data, double x, double y) {
    int i;
    int j;

    i = ( x) / SIZE;
    j = ( y) / SIZE;
    if (i < 0 || i >= 20 || j< 0 || j >= 20)
        return 1; 

    if (data->map[j][i] == '1')
        return (1);
    return (0);
}