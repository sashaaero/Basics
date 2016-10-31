#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

bool inCircle(float x, float y, float i, float j){
    return (pow((x - i), 2) + pow((y - j), 2)) < 1;
}

bool outOfCircle(float x, float y, float i, float j){
    return (pow((x - i), 2) + pow((y - j), 2)) > 1;
}

void lab2(){
    int zone;
    float x, y, area;

    std::cout << "Введите координаты точки ";
    std::cin >> x >> y;

    while(not(-2 < x and x < 2 or -2 < y and y< 2)){
        std::cout << "Неверный ввод\nПовторите >> ";
        std::cin >> x >> y;
    }

    if(x < 0 and outOfCircle(x, y, 0, 0) and inCircle(x, y, 0, 1))
        zone = 1;
    else if(inCircle(x, y, 0, 0) and inCircle(x, y, 0, 1) and inCircle(x, y, 1, 0))
        zone = 2;
    else if(y < 0 and y > -1 and x < 0 and outOfCircle(x, y, 0, 0))
        zone = 3;
    else if(y < 0 and inCircle(x, y, 0, 0) and inCircle(x, y, 1, 0))
        zone = 4;
    else if(x > 1 and y < 0 and outOfCircle(x, y, 1, 0))
        zone = 5;
    else
        zone = 0;

    switch(zone){
        case 1:
            area = M_PI_2 - ((M_PI / 3) - (0.5 * sqrt(0.75))); // Полкруга - парабола
            break;
        case 2:
            area = 2 * ((M_PI / 3) - (0.5 * sqrt(0.75))) - M_PI_4; // (pi/4) - 2((pi/4) - парабола)
            break;
        case 3:
        case 5:
            area = 1 + (1 - M_PI_4);
            break;
        case 4:
            area = (M_PI / 3) - (0.5 * sqrt(0.75));
            break;
        case 0:{
            std::cout << "Точка (";
            std::cout << x << ";" << y;
            std::cout << ") не принадлежит ни одной из зон" << std::endl;
            return;
        }
    }

    std::cout << "Точка (";
    std::cout << x << ";" << y;
    std::cout << ") лежит в зоне M" << zone << " и ее площадь равна " << area << std::endl;
}
