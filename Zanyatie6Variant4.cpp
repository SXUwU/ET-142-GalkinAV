#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Написать программу, которая проверяет, является ли введенная с клавиатуры квадратная матрица «магическим» квадратом.
// «Магическим» квадратом называется матрица, у которой сумма чисел в каждом горизонтальном ряду, в каждом вертикальном и по каждой из диагоналей одна и та же.
// [n × (n² + 1)] / 2 где n - размерность

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int size;
    cout << "Введите размерность квадратной матрицы (одно число): ";
    scanf("%i", &size);
    
    // сумма, которая должна быть у магического квадрата размерностью size
    int sum_square = size*(size*size + 1) / 2;

    // матрица
    int array[size][size];

    int all_sum[size*2 + 2];
    for(int i = 0; i < size*2 + 2; i++){
        all_sum[i] = 0;
    }

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout << "Введите число, которое будет стоять на [" << i+1 << ", " << j+1 << "] месте: ";
            scanf("%i", &array[i][j]);

            all_sum[i] += array[i][j];

            if(i == j){
                all_sum[size*2] += array[i][j];
            }

            if (i + j == size - 1){
                all_sum[size*2 + 1] += array[i][j];
            }
        }   
    }

    for(int j = 0; j < size; j++){
        for(int i = 0; i < size; i++){
            all_sum[size + i] += array[j][i];
        }
    }

    for(int s = 0; s < size*2 + 2; s++){
        if(all_sum[s] != sum_square){
            cout << "Матрица не является магическим квадратом!";
            return 1;
        }
    }

    cout << "Данная матрица - магический квадрат!";

    // for(int i = 0; i < size; i++){
    //     for(int j = 0; j < size; j++){
    //         printf("A[%i][%i] = %i\n", i+1, j+1, array[i][j]);
    //     }
    // }

    // for(int i = 0; i < size*2+2; i++){
    //     cout << all_sum[i] << " ";
    // }

    return 0;
}