#include "cub3d.h"

void my_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;

    dst = img->img_data + y * img->line_len + (x * (img->bpp / 8));
    *(unsigned int *)dst = color;
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


 my_pixel_put(data, data->player_x, data->player_y, 0x00FFFF) ;
 my_pixel_put(data, data->player_x, data->player_y+1, 0x00FFFF) ;
 my_pixel_put(data, data->player_x+1, data->player_y, 0x00FFFF) ; 
 my_pixel_put(data, data->player_x-1, data->player_y, 0x00FFFF) ;
 my_pixel_put(data, data->player_x, data->player_y-1, 0x00FFFF) ;
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
    int i = 0;
    double angl;
    double angl1;
    int x_wall, y_wall;

    int num_rays = 20*19; 
    double fov = M_PI / 3; 

    angl = -fov / 2; 

    while (i < num_rays) {
        angl1 = data->teta + angl;
        normalize_angl(&angl1);
        intr_horizontal(data, &x_wall, &y_wall, angl1);
        draw_line(data, (int)data->player_x, (int)data->player_y, x_wall, y_wall);
        i++;
        angl += fov / num_rays; 
    }
}



void intr_horizontal(t_data *data, int *x_wall, int *y_wall, double angl) {
    int y_intr;
    double x_intr;
    double dx, dy;
    double new_x, new_y;
    t_dir dir;

    dir_r(&dir, angl);
    if (dir.down == 1) {
        y_intr = ((int)data->player_y / SIZE) * SIZE + SIZE;
    } else {
        y_intr = ((int)data->player_y / SIZE) * SIZE   ;
    }
    x_intr = data->player_x + (y_intr - data->player_y) / tan(angl);
    dy = (dir.down == 1) ? -SIZE : SIZE;
    dx = dy / tan(angl);

    new_x = x_intr;
    new_y = y_intr;
    while (!check_wall(*data, new_x, new_y)) {
        new_x += dir.right*dx;
        new_y +=dir.down*dy;
    }

    *x_wall = (int)new_x;
    *y_wall = (int)new_y;
}

int check_wall(t_data data, double x, double y) {
    int new_x = (int)floor(x / SIZE);
    int new_y = (int)floor(y / SIZE);

    if (new_x < 0 || new_x >= 20 || new_y < 0 || new_y >= 19)
        return 1; 

    if (data.map[new_y][new_x] == '1')
        return 1;
    return 0;
}