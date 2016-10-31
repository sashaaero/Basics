#include <iostream>
#define N 10
#define M 5

void arrayTask(){
    int cs(-1), ce(-1), ms(-1), me(-1); // current start/end, max start/end
    int array[N];
    std::cout << "Введите " << N << " элементов массива" << std::endl;
    for(int i = 0; i < N; i++){
        std::cin >> array[i];
        if(array[i] == 0){
            if(cs == -1){
                cs = i;
                ce = i;
            } else {
                ce++;
                if(i == 9 and (me - ms) < (ce - cs)){
                    ms = cs;
                    me = ce;
                }
            }

        } else {
            if(cs != -1 and (me - ms) < (ce - cs)){
                ms = cs;
                me = ce;
            }
            cs = -1;
        }
    }
    if(ms != -1){
        printf("Секвенция длинной %d, начало: %d, конец: %d\n", (me - ms + 1), ms, me);
    } else {
        std::cout << "Нулей в массиве нет" << std::endl;
    }
}

void printMatrix(int matrix[][M]){
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void matrixTask(){
    int mni(-1), mnj(-1); // max negative i/j
    int matrix[M][M];
    std::cout << "Ввод матрицы (5x5)" << std::endl;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            std::cin >> matrix[i][j];
            if(matrix[i][j] < 0){
                if(mni == -1 or matrix[i][j] > matrix[mni][mnj]){
                    mni = i;
                    mnj = j;
                }
            }
        }
    }

    std::cout << "Результат " << std::endl;
    
    if(mni != -1 and mnj != -1){
        for(int j = 0; j < M; j++){
            int tmp = matrix[M-1][j];
            matrix[M-1][j] = matrix[mni][j];
            matrix[mni][j] = tmp;
        }
    }

    printMatrix(matrix);
}

void lab4(){
    unsigned short task;
    std::cout << "Задание ";
    std::cin >> task;
    switch(task){
        case 1:
            arrayTask();
            break;
        case 2:
            matrixTask();
            break;
        default:
            std::cout << "Неверный номер " << std::endl;
            break;
    }
}
