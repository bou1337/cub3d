

#include "cub3d.h"
 
void   normalize_angl(double *angl)
{
    int  k  ; 

    k = *angl /(2*M_PI) ;
    *angl = *angl -k*(2*M_PI) ;

    if(*angl<0)
    *angl = *angl +2*M_PI ;
}

int  main()
{

    double  angl =  -M_PI  ;
    t_dir dir ;
    normalize_angl(&angl) ;
     dir_p(&dir, angl) ;
     if(dir.down)
     {
        printf("the  player looks  down\n") ;
     }
     if(dir.up)
     printf("the  player looks up\n") ;
     if(dir.left)
     {
        printf("the  player looks left \n") ;
     }
     if(dir.right)
     {
        printf("the  player looks right\n") ;
     }

}
