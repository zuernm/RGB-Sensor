#include <iostream>
#include <string>

#include "Sensor.h"

int main(int argc, char **argv)
{          
        Sensor rgb;
        
        if (argc <= 1){
           std::cout << rgb.dominantColor() << std::endl;          
        }
        
        if (argc == 2){
            if (std::string(argv[1]) == "loop"){
               int color;
               while (true){
                sleep(1);   
                std::cout << rgb.dominantColor() << std::endl;                         
               }
            }
            if (std::string(argv[1]) == "print"){
                unsigned int blue = rgb.readBlue();
                std::cout << "Blue: " << blue << std::endl;                
                unsigned int red = rgb.readRed();
                std::cout << "Red: " << red << std::endl;                
                unsigned int green = rgb.readGreen();
                std::cout << "Green: " << green << std::endl;   
                std::cout << "Dominant Color: " << rgb.dominantColor() << std::endl;
            }            
        }
        
        return 0;
        
}
