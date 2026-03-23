#include <iostream>
#include <math.h>

using namespace std;

const int K = 6;

void swal(int &x, int &y){
    x = x+y;
    y = x-y;
    x = x-y;

    cout << x << " " << y;
}

float f1(float x){
    return sin(x)/x;
}

float f2(float x){
    return x*x + 2*pow(x, 3.0/2.0);
}


float f3(float x){
    return (x+2)*(x+1)*x;
}


// float(*y) (float) второй float - тип функции, первый реузльтат вывода функции
// вместо y будет подставлять название функции
void print(float x, float(*y) (float)){
    cout <<  y(x) << endl;

}

float max(float a, float b){
    return a > b ? a : b;
}

float min(float a, float b){
    return a < b ? a : b;
}

float max(float* y){
    float m = y[0];

    for(int i = 1; i < sizeof(y); i++){
        m = max(m, y[i]);
    }

    return m;
}

float min(float* y){
    float m = y[0];

    for(int i = 1; i < K; i++){
        m = min(m, y[i]);
    }

    return m;
}

// Задание 4* под цифрой 1
float function1(float x, float e){
    int n = 2;
    
    float res = 0;

    float i = x;

    while(abs(i) >= e){
        res += i;

        i = (pow(x, 2*n - 1))/(2.0*n - 1.0);
        
        n++;
        
        printf("%i\t%f\t%f\n", n, i, res);
    }

    return res;
}

void function2(float* x, float* e, float* result){
    int n = 2;

    float i = *x;

    while(abs(i) >= *e){
        *result += i;

        i = (pow(*x, 2*n - 1))/(2.0*n - 1.0);

        n++;
    }
}

int main(){
// Задание 4* под цифрой 2
    float result = 0;
    float x = 0.2;
    float e = 0.5*pow(10,-4);

    function2(&x, &e, &result);
    cout << result;
// Конец задания 4* под цифрой 1


    // int x = 5;
    // int y = -3;
    // swal(x,y);
    // float x = 0.6f;
    // float y = 0.3f;
    // float z = 0.1f;

    // cout << "f1(x): " << endl;
    // print(x, f1);

    // cout << "f2(x): " << endl;
    // print(y, f2);

    // cout << "f3(x): " << endl;
    // print(z, f3);
    
    // cout << f1(x) + f2(y) * f3(f2(z));
    
    // float y[K];
    // srand(time(0));
    // for(int i = 0; i < sizeof(y)/sizeof(float); i++){
    //     y[i] = (float) rand()/rand();
        
    //     cout << y[i] << " ";
    // }

    // cout << "\n";

    // cout << "Max: " << max(y) << endl;
    // cout << "Min: " << min(y) << endl;

    return 0;
}