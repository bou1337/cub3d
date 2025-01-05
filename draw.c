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
draw_line(data,data->player_x , data->player_y , data->player_x +70*cos(data->teta), data->player_y+70*sin(data->teta)) ;
 draw_line(data,data->player_x , data->player_y , data->player_x +70*cos(data->teta+FOV/2), data->player_y+70*sin(data->teta+FOV/2)) ;
 draw_line(data,data->player_x , data->player_y , data->player_x +70*cos(data->teta-FOV/2), data->player_y+70*sin(data->teta-FOV/2)) ;
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
    angl =  -M_PI/(double)6 ;

    while( i < 30*20 )
    {

        draw_line ( data , data->player_x , data->player_y , data->player_x + 40*cos(data->teta +angl) , data->player_y +40*sin(data->teta +angl)) ;
        i++ ;
        angl += M_PI/(3*(30*20 ))  ;
    }
 }