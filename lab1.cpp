#include <iostream>

void lab1(){
    unsigned char res;
    res = 125 & 20;
    std::cout << "119 AND 20 = " << (int) res << std::endl;
    res = 125 | -20;
    std::cout << "119 OR -20 = " << (int) res << std::endl;
    res = 50 << 2;
    std::cout << "50 <- 2 = " << (int) res << std::endl;
    res = 40 | ~-19 & (~50 ^ -7);
    std::cout << "40 OR NOT -19 AND (NOT 50 XOR -7) = " << (int) res << std::endl;
}
