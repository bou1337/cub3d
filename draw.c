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

 void   draw_rays(t_data  * data)
 {

    int  i  ;
    i  = 0  ;
    double  angl  ;
    double angl1 ; 
    int x_wall ;
    int  y_wall ;
    angl =  -M_PI/(double)6 ;

    while( i < 1 )
    {
        angl1 = data->teta + angl  ;
        normalize_angl(&angl1) ;
        intr_horizontal(data, &x_wall, &y_wall,angl1);
        draw_line ( data , data->player_x , data->player_y , x_wall ,y_wall) ;
        i++ ;
        angl += M_PI/(3*(30*20 ))  ;
    }
 }




 void intr_horizontal(t_data *data ,int  *x_wall, int  *y_wall, double angl)
 {
   

    int x_intr ; 
    int y_intr ;
    double new_x ;
    double new_y ;
    double dx ;
    double dy  ;
    y_intr = ((int)data->planeY)*SIZE  ;
    x_intr = data->player_x + (y_intr - data->player_y)/tan(angl) ;
    dy  =SIZE ;
    dx = dy/tan(angl) ;
    new_x = x_intr ;
    new_y = y_intr ;
    while(!check_wall(*data ,new_x , new_y))
    {
        new_x +=dx ;
        new_y +=dy ;
    }
    *x_wall = new_x  ;
    *y_wall = new_y ;
 }

 int check_wall(t_data  data , double x , double y)
 {

    int new_x ;
    int new_y ;

    new_x = x/SIZE ;
    new_y = y/SIZE ;
    if(data.map[new_x][new_y]=='1')
    return 1 ;
    return 0 ;
 }