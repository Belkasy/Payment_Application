/**
 * @name            main.c
 * @def             part of pyment system project - FWD
 * @version         v1.0
 * @authors         Abdelrahman Belkasy
 * @date            21 August 2022
*/
#include <stdio.h>
#include <string.h>
#include "Application/app.h"
/*                             Data Base                                */ 

/*        Balance                      PAN                              */     
//    {   100.5       ,       "4847 3529 8926 3094"    },     /* user 1 */
//    {   200.111     ,       "3379 5135 6110 8795"    },     /* user 2 */
//    {   500.21      ,       "4904 8398 2248 5959"    },     /* user 3 */
//    {   10.100      ,       "2769 1483 0405 9987"    },     /* user 4 */
//    {   1000        ,       "1234 5675 9876 5432"    },     /* user 5 */
//    {   1002.6      ,       "9131 4617 8375 9183"    },     /* user 6 */
//    {   5123.3      ,       "0490 9912 9683 4267"    }      /* user 7 */ 

int main(void) 
{
    while (1)
    {
        char status[5]="";

        appStart();
        
        printf("\nTo Exit Enter Any Key");
        printf("\nTo Exit Enter 0");
        printf("\n>>>>>>>>>> ");
        gets(status);
        printf("----------------------------------------------------------------------------\n");

        if (strcmp(status,"0") == 0) {break;}
    }
    return 0;    
}