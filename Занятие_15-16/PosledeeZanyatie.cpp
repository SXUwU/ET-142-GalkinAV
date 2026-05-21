//
// Created by Aleks on 20.05.2026.
//
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;

vector<int> sortVector(vector<int> v) {
    // Альтернатива
    // sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) {
        for (int j = v.size() - 1; i < j; j--) {
            if (v.at(j) < v.at(j-1)) {
                swap(v.at(j), v.at(j-1));
            }
        }
    }

    return v;
}

vector<int> reverseVector(vector<int> v) {
    //reverse(v.begin(), v.end());

    for (int i = 0; i < v.size()/2; i++) {
        swap(v.at(i), v.at(v.size()-1-i));
    }

    return v;
}

int sum(vector<int> arr) {
    // int n = accumulate(arr.begin(), arr.end(), 0);
    int n = 0;

    for (int i = 0; i < arr.size(); i++) {
        n += arr.at(i);
    }

    return n;
}

int findFrequency(vector<int> arr, int x) {
    // int i = count(arr.begin(),arr.end(),x);
    //-------------------------
    
    int i = 0;

    // for (int num: arr) {
    //     if (num == x) {
    //         i++;
    //     }
    // }

    //-------------------------

    for (int num = 0; num < arr.size(); num++) {
        if (arr.at(num) == x) {
            i++;
        }
    }

    return i;
}

int main() {
    // vector<int> vec = {1,4,2,4,3,4};
    //
    // cout << count(vec.begin(),vec.end(),4) << endl;
    // cout << findFrequency(vec, 4) << endl;

    // int n = accumulate(vec.begin(), vec.end(), 0);
    // cout << n << endl;
    //
    // for (int i = 0; i < vec.size(); i++) {
    //     cout << vec.at(i) << " ";
    // }



    srand(static_cast<unsigned int>(time(nullptr)));

    Eigen::MatrixXd a = Eigen::MatrixXd::Random(500,500);
    Eigen::MatrixXd b = Eigen::MatrixXd::Random(500,500);

    cout << "Матрица a: " << "\n" <<  a.block(0,0,3,3) << "\n";
    cout << "---" << "\n";
    cout << "Матрица b: " << "\n" << b.block(0,0,3,3) << endl;
    //начало временного отрезка
    auto start = chrono::high_resolution_clock::now();

    a = a.inverse();

    Eigen::MatrixXd x = a*b;


    auto end = chrono::high_resolution_clock::now();

    cout << "---" << "\n" << "Обратная матрица a: " << "\n";
    cout << a.block(0,0,3,3) << "\n";
    cout << "---" << endl;

    cout << "Результат вычислений уравнения Ax = B:" << "\n";
    cout << x.block(0,0,3,3) << endl;

    //вычисление длительности по времени в секундах
    chrono::duration<double> duration = end - start;
    //вычисление длительности по времени в миллисекундах (действует округление)
    chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(duration);
    //вывод времени в секундах
    cout << duration.count() << " s" << endl;
    //вывод времени в миллисекундах
    cout << ms.count() << " ms" << "\n" << endl;
    //----------------------------------------------------------------------------------------------------------------

    //-----------------------------------Транспонирование матрицы-----------------------------------------------------

    Eigen::MatrixXi mat_a = Eigen::MatrixXi::Random(150,100);
    Eigen::MatrixXi mat_a_tr = mat_a.transpose();
    cout << "---" << "\n" << "Транспонирование матрицы: " << "\n";
    cout << mat_a.block(0,0,3,3) << "\n";
    cout << "---" << "\n";
    cout << mat_a_tr.block(0,0,3,3) << endl;

    //----------------------------------Вектора с использованием библиотеки------------------------------------------
    Eigen::VectorXd x1 = Eigen::VectorXd::Random(100000);
    Eigen::VectorXd y = Eigen::VectorXd::Random(100000);

    cout << "------Примеры значений в векторах-------" << "\n";
    cout << x1[0] << " " << x1[1] << " " << y[0] << " " << y[1] << endl;
    cout << "-------------" << endl;

    auto start_dot = chrono::high_resolution_clock::now();

    double d = x1.dot(y);

    auto end_dot = chrono::high_resolution_clock::now();

    chrono::duration<double> duration_dot = end_dot - start_dot;
    std::chrono::duration<double, std::milli> ms_dot = chrono::duration_cast<chrono::milliseconds>(duration_dot);


    auto start_norm = chrono::high_resolution_clock::now();

    double result_x = x1.norm();

    auto end_norm = chrono::high_resolution_clock::now();

    chrono::duration<double> duration_norm = end_norm - start_norm;
    std::chrono::duration<double, std::milli> ms_norm = chrono::duration_cast<chrono::milliseconds>(duration_norm);


    cout << "Время выполнения с использованием библиотеки Eigen (скалярное произведение и евклидова норма):" << endl;
    cout << "Скалярное произведение мс: " << duration_dot.count() << endl;
    cout << "Евклидова норма мс: " << duration_norm.count() << endl;
    cout << "Скалярное произведение и евклидова норма: " << d << " " << result_x << "\n" << endl;
    //----------------------------------------------------------------------------------------------------------------


    //----------------------------------Вектора без использования библиотеки------------------------------------------
    // double vec1[100000];
    // double vec2[100000];
    vector<double> vec1(100000);
    vector<double> vec2(100000);

    for (int i = 0; i < vec1.size(); i++) {
    //     vec1[i] = 10 + rand() % (100 - 1 + 1);
    //     vec2[i] = 10 + rand() % (100 - 1 + 1);

        vec1.at(i) = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        vec2.at(i) = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    }


    cout << "-------Примеры значений в векторах без использования библиотеки Eigen------" << "\n";
    cout << vec1[0] << " " << vec2[1] << "\n";
    cout << "-------------" << endl;

    double dot = 0;
    double norm = 0;


    auto start_dot_without = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        dot += vec1.at(i)*vec2.at(i);
    }
    auto end_dot_without = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_dot_without = end_dot_without - start_dot_without;


    auto start_norm_without = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        norm += vec1.at(i)*vec1.at(i);
    }
    norm = sqrt(norm);
    auto end_norm_without = chrono::high_resolution_clock::now();

    chrono::duration<double> duration_norm_without = end_norm_without - start_norm_without;

    cout << "Время выполнения без использования библиотеки Eigen:" << "\n";
    cout << "Скалярное произведение мс: " << duration_dot_without.count() << endl;
    cout << "Евклидова норма мс: " << duration_norm_without.count() << endl;
    cout << "Скалярное произведение и евклидова норма: " << dot << " " << norm << endl;

    //----------------------------------------------------------------------------------------------------------------

    return 0;
}