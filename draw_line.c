
#include  "cub3d.h"

void draw_line(t_data *data , double x0 , double y0 , double x1, double y1)
{

    int step ; 
    int dx ;
    int dy ;
    int i ; 

    i = 0 ;
    dx = x1 -x0 ;
    dy = y1 -y0 ;
    step = (abs(dx)>abs(dy)? abs(dx): abs(dy)) ;
    float Xinc ;
    float Yinc ;

    Xinc = dx/(float)step ;
    Yinc = dy/ (float)step ;
    float x ;
    float y ;
    x = x0 ;
    y = y0 ;
    while(i<step)
    {
        my_pixel_put(data, (int)x, (int)y,0xFF0000);
        x+=Xinc ;
        y += Yinc ;
        i++ ;
    }

}