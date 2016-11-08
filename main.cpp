#include <iostream>
#include "functions.h"

int main(){
    unsigned int lab;
    while(true){
        std::cout << "Enter lab number >> ";
        std::cin >> lab;
        switch(lab){
            case 1:
                lab1();
                break;
            case 2:
                //lab2();
                break;
            case 3:
                lab3();
                break;
            case 4:
                lab4();
                break;
            case 6:
                lab6();
                break;
            case 8:
                lab8();
                break;
            case 9:
                lab9();
                break;
            case 10:
                lab10();
                break;
            case 0:
                return 0;
            default:
                std::cout << "This lab does not exist" << std::endl;
                break;
        }
    }
}

