

#include "cub3d.h"

void draw_rect(t_data *data, int x, int y, int color)
{
    int start_x = x *8;
    int start_y = y * 8;
    int end_x = start_x + 8;
    int end_y = start_y + 8;
    int i ; 
    int j ;
    i = start_x ;
    
    while(i<end_x)
    {
         j= start_y ;
        while( j < end_y)
        {        
            put_color_to_pixel(data, i, j, color);
            j++ ;
        }
        i++ ;
    }
}

void draw_mapp(t_data *data)
{
    int i  = 0 ;
    int j  = 0  ;
    while(i<data->map.height)
    {       
        j = 0 ;
        while(j<data->map.width)
        {
            if (data->map.map[i][j] == '1')
                draw_rect(data, j, i, 0x0000FF); 
            else
                draw_rect(data, j, i, 0xFFFFFF);
                j++ ; 
        }
        i++ ;
}
}

void draw_line(t_data *data , double x0 , double y0 , double x1, double y1)
{

    double step ; 
    double dx ;
    double dy ;
    int i ; 

    i = 0 ;
    dx = x1 -x0 ;
    dy = y1 -y0 ;
    step = (abs(dx)>abs(dy)? abs(dx): abs(dy)) ;
    float Xinc ;
    float Yinc ;

    Xinc = dx/step ;
    Yinc = dy/step ;
    float x ;
    float y ;
    x = x0 ;
    y = y0 ;
    while(i<step)
    {   
        put_color_to_pixel(data, (int)x, (int)y,0xFF0000);
        x+=Xinc ;
        y += Yinc ;
        i++ ;
    }

}