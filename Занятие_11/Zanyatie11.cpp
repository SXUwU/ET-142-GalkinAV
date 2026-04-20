#include <iostream>
///#include <bits/valarray_after.h>

using namespace std;

// class A {
//     int x;
//     int y;
//
//     public:
//     A(int x = 0, int y = 0);
//
// };
//
// void A::A(int x, int y) {
//     this->x = x;
//     this->y = y;
// }

class B {
    int i;

    public:
    B() {
        this->i = 10;
    }

    B(B& obj) {
        this->i = obj.i + 10;
    }

    int get();

};
// 10 20 30

int B::get() {
    return i;
}


int NOD(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        }
        else {
            b = b % a;
        }
    }
    return a+b;
}

class Fraction {
    int chisl;
    int znam;

    public:
        Fraction(int chisl1, int znam1) {
            chisl = chisl1;
            znam = znam1;
        }

        Fraction operator+(Fraction b) {
            int x = chisl * b.znam + b.chisl * znam;
            int y = znam * b.znam;

            int n = NOD(x, y);
            x = x / n;
            y = y / n;

            return Fraction(x, y);

        }

    Fraction operator-(Fraction b) {
            int x = chisl * b.znam - b.chisl * znam;
            int y = znam * b.znam;

            int n = NOD(x, y);
            x = x / n;
            y = y / n;

            return Fraction(x, y);

        }


    Fraction operator*(Fraction b) {
            int x = chisl * b.chisl;
            int y = znam * b.znam;

            int n = NOD(x, y);
            x = x / n;
            y = y / n;

            return Fraction(x, y);

        }

    Fraction operator/(Fraction b) {
            int x = chisl * b.znam;
            int y = znam * b.chisl;

            int n = NOD(x, y);
            x = x / n;
            y = y / n;

            return Fraction(x, y);

        }

    void print() {
            cout << chisl << "/" << znam << endl;
        }
};

class Complex {
    float re;
    float im;

    public:
        Complex(float re = 0, float im = 0) {
            this->re = re;
            this->im = im;
        }

        Complex operator+(Complex y) {
            float a = re + y.re;
            float b = im + y.im;

            return Complex(a,b);
        }

        Complex operator-(Complex y) {
            float a = re - y.re;
            float b = im - y.im;

            return Complex(a,b);
        }

        Complex operator*(Complex y) {
            float a = re*y.re - im*y.im;
            float b = re*y.im + y.re*im;

            return Complex(a,b);
        }

        Complex operator/(Complex y) {
            float a = (re*y.re + im*y.im)/(y.re*y.re + y.im*y.im);
            float b = (im*y.re - re*y.im)/(y.re*y.re + y.im*y.im);

            return Complex(a,b);
        }

        void print() {
            if (im < 0) {
                cout << re << im << "i" << endl;
            } else if (im == 0) {
                cout << re << endl;
            } else if (re == 0) {
                cout << im << "i" << endl;
            }else {
                cout << re << "+" << im << "i" << endl;
            }
        }
};

void pow_compl(Complex& base, int exp) {
    if (exp == 0) {
        base = Complex(1);
    }

    Complex orig_base = base;

    for (int i = 2; i <= exp; i++) {
        base = base*orig_base;
    }
}

int main() {
    Complex x(10, 5);
    Complex y(13, 4);
    Complex result(1,2);
    pow_compl(result, 2);
    result.print();



    // Fraction f1(3,4);
    // Fraction f2(5,6);
    // Fraction f3 = f1 + f2;
    // Fraction f4 = f1 - f2;
    //
    // f3.print();
    // f4.print();

    // B b1, b2 = b1, b3(b2);
    // cout << b1.get() << b2.get() << b3.get() << endl;

    return 0;
}