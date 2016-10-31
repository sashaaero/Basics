#include <iostream>
#include <cmath>

double fakeRecurrencyWhile(int m, double y0, double y1, double y2){
    int i = 4;
    double yi = pow(sin(y2), 2) + pow(cos(y0), 2);
    while(i < m){
        y0 = y1;
        y1 = y2;
        y2 = yi;
        yi = pow(sin(y2), 2) + pow(cos(y0), 2);
        i++;
    }
    return yi;
}

double fakeRecurrencyDoWhile(int m, double y0, double y1, double y2){
    int i = 3;
    double yi;
    do{
        yi = pow(sin(y2), 2) + pow(cos(y0), 2);
        y0 = y1;
        y1 = y2;
        y2 = yi;
        i++;
    } while(i < m);
    return yi;
}

double fakeReccurencyFor(int m, double y0, double y1, double y2){
    double yi;
    for(int i = 3; i < m; i++){
        yi = pow(sin(y2), 2) + pow(cos(y0), 2);
        y0 = y1;
        y1 = y2;
        y2 = yi;
    }
    return yi;
}

void fakeReccurency(){
    unsigned int m = 0;
    double y0, y1, y2;
    while(m <= 3){
        std::cout << "Задайте m (>3) >> ";
        std::cin >> m;
    }
    std::cout << "Задайте y0 >> ";
    std::cin >> y0;
    std::cout << "Задайте y1 >> ";
    std::cin >> y1;
    std::cout << "Задайте y1 >> ";
    std::cin >> y2;

    std::cout << "Вычисления через while " << fakeRecurrencyWhile(m, y0, y1, y2) << std::endl;
    std::cout << "Вычисления через do while " << fakeRecurrencyDoWhile(m, y0, y1, y2) << std::endl;
    std::cout << "Вычисления через for " << fakeReccurencyFor(m, y0, y1, y2) << std::endl;
}

double limitWhile(double A, double eps){
    eps = 1 / eps;
    double prev = A + 1;
    double curr = 2 * (2 + A);
    int n = 3;
    while(std::abs(prev - curr) < eps){
        prev = curr;
        curr = n * (n + A);
        n++;
    }
    return 1 / curr;
}

double limitDoWhile(double A, double eps){
    eps = 1 / eps;
    double prev = A + 1;
    double curr = 2 * (2 + A);
    int n = 3;
    do{
        prev = curr;
        curr = n * (n + A);
        n++;
    } while(std::abs(prev - curr) < eps);
    return 1 / curr;
}

double limitFor(double A, double eps){
    eps = 1 / eps;
    double prev = A + 1;
    double curr = 2 * (2 + A);
    for(int n = 3; std::abs(curr - prev) < eps; n++){
        prev = curr;
        curr = n * (n + A);
    }
    return 1 / curr;
}

void limit(){
    double A, eps;
    std::cout << "Задайте A >> ";
    std::cin >> A;
    std::cout << "Задайте точность >> ";
    std::cin >> eps;

    std::cout << "Вычисления цикла while " << limitWhile(A, eps) << std::endl;
    std::cout << "Вычисления цикла do while " << limitDoWhile(A, eps) << std::endl;
    std::cout << "Вычисления цикла for " << limitFor(A, eps) << std::endl;
}

void lab3(){
    unsigned short task;
    std::cout << "Задание ";
    std::cin >> task;
    switch(task){
        case 1:
            fakeReccurency();
            break;
        case 2:
            limit();
            break;
        default:
            std::cout << "Неверный номер ";
            break;
    }
}
