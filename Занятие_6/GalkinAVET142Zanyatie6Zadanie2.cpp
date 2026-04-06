#include <iostream>
#include <string>

using namespace std;


// Дана строка. Сколько слов имеют длину, равную N символам?

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // char list_of_symbols[] = {',', '.', '?', '!', ':', ' ', ';'};

    string str;
    cout << "Введите строку: ";
    getline(cin, str);
    str += " ";

    int n;
    cout << "Введите количество букв, которое должно быть в слове: ";
    scanf("%i", &n);

    int count = 0;

    int pos1 = 0;
    int pos2;

    while (pos2 != string::npos){
        pos2 = str.find(" ", pos1);

        int length_of_word = pos2 - pos1;

        if (length_of_word == n){
            count++;
        }

        pos1 = pos2 + 1;
    }

    printf("Количество слов: %i", count);

    return 0;
}
