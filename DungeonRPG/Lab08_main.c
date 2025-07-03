// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"



// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****

// **** Declare any function prototypes here ****

int main()
{



    /******************************** Your custom code goes below here ********************************/
    GameInit();
    
    char input = '\0';
    
    while (1) {
    
        printf("\nPick a direction (n = north, e = east, s = south, w = west, q = quit): ");
        scanf(" %c", &input);
        
        if (input == 'n') {
            GameGoNorth();
        }
        
        if (input == 'e') {
            GameGoEast();
        }
        
        if (input == 's') {
            GameGoSouth();
        }
        
        if (input == 'w') {
            GameGoWest();
        }
        
        if (input == 'q') {
            break;
        }
    }
    
    
    
    



    /**************************************************************************************************/
}

