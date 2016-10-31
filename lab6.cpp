#include <iostream>

int partition(int *array, int left, int right) {
    int mid = left + (right - left) / 2;
    int pivot = array[mid];
    std::swap(array[mid], array[left]);
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while(i <= j and array[i] <= pivot) {
            i++;
        }

        while(i <= j and array[j] > pivot) {
            j--;
        }

        if (i < j) {
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i - 1], array[left]);
    return i - 1;
}

void quicksort(int* array, int left, int right, int size){
    if (left >= right)
        return;

    int part = partition(array, left, right);
    quicksort(array, left, part - 1, size);
    quicksort(array, part + 1, right, size);
}

void printMatrix(int** matrix, int size){
    system("clear");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl << std::endl;
    }
}

void lab6(){
    int curr_in, size, len;
    std::cout << "Введите размер матрицы >> ";
    std::cin >> size;

    len = size * size;
    int** matrix = new int*[size];
    int* array = new int[len];

    for(int i = 0; i < size; i++){
        matrix[i] = new int[size];
        for(int j = 0; j < size; j++){
            std::cin >> curr_in;
            array[i * size + j] = curr_in;
        }
    }

    quicksort(array, 0, len - 1, len);

    bool increase = true;
    int i(0), j(0), x(0), step(0), way(0);
    enum ways{right, downleft, down, upright};

    matrix[0][0] = array[0];

    while(x < len - 1){
        switch(way){
            case right:{
                matrix[i][++j] = array[++x];
                way = increase ? downleft : upright;
                break;
            }
            case downleft:{
                step += increase ? 1 : -1;
                for(int s = 0; s < step; s++)
                    matrix[++i][--j] = array[++x];
                if(step == (size - 1))
                    increase = false;
                way = increase ? down : right;
                break;
            }
            case down:{
                matrix[++i][j] = array[++x];
                way = increase ? upright : downleft;
                break;
            }
            case upright:{
                step += increase ? 1 : -1;
                for(int s = 0; s < step; s++)
                    matrix[--i][++j] = array[++x];
                if((size % 2 == 1) and increase)
                    increase = !(step == size - 1);
                way = increase ? right : down;
                break;
            }
        }
    }
    printMatrix(matrix, size);
    delete[] matrix;
    delete[] array;
}
