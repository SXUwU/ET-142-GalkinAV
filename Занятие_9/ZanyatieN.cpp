#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

struct timeap{
    int hour;
    int min;
    int sec;
};

struct airplane {
    string arrive_point;

    timeap t_go;
    timeap t_end;
    timeap t_trip;

    float cost;

    string type_flight;

};


void print_flight(airplane &flight) {
    /*Вывод информации объектра структуры airplane
     * flight (airplane): объект структуры airplane
     */

    cout << "----------------" << endl;
    cout << "Город назначения: " << flight.arrive_point << "; Стоимость: " << flight.cost << "; Тип полета: " << flight.type_flight << endl;
    cout << "Время отправки: " << flight.t_go.hour << ":" << flight.t_go.min << endl;
    cout << "Время прибытия: " << flight.t_end.hour << ":" << flight.t_end.min << endl;
    cout << "Время в пути: " << flight.t_trip.hour << ":" << flight.t_trip.min << endl;
    cout << "----------------" << endl;
}


bool elem_is_ex(airplane arr[], int size, airplane elem){
    /* Функция, проверяющая наличие объекта структуры airplane в базе данных
     * arr[] (airplane): массив, в котором нужно найти объект
     * size (int): размеронсть массива
     * elem (airplane): объект, который нужно найти
     *
     * return: bool
     */

    for(int i = 0; i < size; i++){
        if(arr[i].arrive_point == elem.arrive_point && arr[i].type_flight == elem.type_flight && 
        arr[i].cost == elem.cost && arr[i].t_trip.hour == elem.t_trip.hour && arr[i].t_trip.min == elem.t_trip.min && 
        arr[i].t_end.hour == elem.t_end.hour && arr[i].t_end.min == elem.t_end.min){
            return true;
        }
    }
    return false;
}

void search_grad(airplane old_arr[], airplane new_arr[], int size){
    /* заполняет новый массив объектами структуры airplane, в которых город оканчивается на "град".
     * old_arr[] (airplane): массив, в котором нужно искать такие объекты
     * new_arr[] (airplane): массив, который заполняется найденными объектами
     * size (int): размерность двух массивов. В худшем случае new_arr[] заполнится всеми объектами из старого массива
     */

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(old_arr[j].arrive_point.find("град") != string::npos && old_arr[j].type_flight == "транзит" && !elem_is_ex(new_arr, size, old_arr[j])){
                new_arr[i] = old_arr[j];
                break;
            }
        }
    }
    cout << "Массив сформирован" << endl;
}


bool compr(airplane a, airplane b){
    /* Вспомогательная функция для сортировки методом пузырька. Сравнение часов и минут для сортировки пузырьком в функции filt_time_arr
     * a (airplane): объект структуры airplane
     * b (airplane): объект структуры airplane
     *
     * Returns:
     *  bool
     */

    return ((a.t_trip.hour < b.t_trip.hour) || ((a.t_trip.hour == b.t_trip.hour) && (a.t_trip.min < b.t_trip.min)));
}

void filt_time_arr(airplane arr[], int size_arr){
    /* Сортировка пузырьком по времени полета
     * arr[] (airplane): массив, который нужно отсортировать
     * size_arr (int): размероность массива
     */

    airplane p;

    for(int i = 0; i < size_arr; i++){
        for(int j = size_arr - 1; j > i; j--){
            if(compr(arr[j-1], arr[j])){
                p = arr[j-1];

                arr[j-1] = arr[j];
                arr[j] = p;
            }
        }
    }

    cout << "Массив отсортирован!" << endl;
}

void search_flight_by_name(airplane arr[], int size) {
    /* Поиск рейса по месту посадки и времени оотправления
     * arr[] (airplane): массив, в котором нужно найти
     * size (int): размероность массива
     */

    string point;
    int hour;
    int min;

    cout << "Введите пункт назначения рейса: ";
    getline(cin, point);

    cout << "Введите время отправки в формате Ч:М : ";
    scanf("%i:%i", &hour, &min);

    printf("Вот вся информация по рейсам в %s:\n", point.c_str());
    for (int i = 0; i < size; i++) {
        if (arr[i].arrive_point == point && arr[i].t_go.hour == hour && arr[i].t_go.min == min) {
            print_flight(arr[i]);
            break;
        }
    }

    cin.ignore(32767, '\n');
}

void print_flights_by_tt(airplane arr[], int size) {
    /* Вывод полетов, которые вылетают в определенном диапазоне
     * arr[] (airplane): массив, котором нужно найти
     * size (int): размероность массива
     */
    int hour1;
    int hour2;
    string type_fl;
    int count;

    cout << "Введите тип рейса: ";
    getline(cin, type_fl);

    cout << "Введите, в каком диапазоне рейсы вылетают в формате Ч-Ч: ";
    scanf("%i-%i", &hour1, &hour2);

    cout << "Сколько рейсов вывести в консоль?: ";
    scanf("%i", &count);

    for (int i = 0; i < size; i++) {
        if (count != 0 && arr[i].type_flight == type_fl && hour1 <= arr[i].t_go.hour && arr[i].t_go.hour < hour2) {
            print_flight(arr[i]);
            count--;
        }
        else if (count == 0) {
            break;
        }
    }

    cin.ignore(32767, '\n');
}

void calc_t_trip(airplane &flight) {
    /* Вычисление времени полета
     * &flight (airplane): ссылка на объект
     */

    if (flight.t_end.hour >= flight.t_go.hour) {
        flight.t_trip.hour = flight.t_end.hour - flight.t_go.hour;
    }
    else {
        flight.t_trip.hour = 24 - flight.t_go.hour + flight.t_end.hour;
    }

    if (flight.t_end.min >= flight.t_go.min) {
        flight.t_trip.min = flight.t_end.min - flight.t_go.min;
    }
    else {
        flight.t_trip.hour--;
        flight.t_trip.min = 60 - flight.t_go.min + flight.t_end.min;
    }
}

void rename_flight(airplane &flight) {
    /* Полное переназначение полета
     * &flight (airplane): ссылка на объект
     */

    cout << "Введите новый пункт назначения: ";
    getline(cin, flight.arrive_point);

    cout << "Введите тип полета: ";
    getline(cin, flight.type_flight);

    cout << "Введите время отправки в формате Ч:М:С: ";
    scanf("%i:%i:%i", &flight.t_go.hour, &flight.t_go.min, &flight.t_go.sec);

    cout << "Введите время прибытия: ";
    scanf("%i:%i:%i", &flight.t_end.hour, &flight.t_end.min, &flight.t_end.sec);

    // Вычисление времени полета
    calc_t_trip(flight);

    cout << "Введите цену: ";
    scanf("%f", &flight.cost);

    cin.ignore(32767, '\n');
}

void search_flight_btc(airplane arr[], int size, airplane new_arr[]) {
    /* Формирование нового массива с полетами, стоимость которых не превышает определенного значения
     * arr[] (airplane): массив со всеми полетами
     * new_arr[] (airplane): массив, который формируется
     * size (int): размерность массивов
     */

    string type_fl;
    cout << "Введите тип полета: ";
    getline(cin, type_fl);

    float cost_fl;
    cout << "Введите предельную стоймость билета: ";
    scanf("%f", &cost_fl);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[j].cost <= cost_fl && arr[j].type_flight == type_fl && !elem_is_ex(new_arr, size, arr[j])) {
                new_arr[i] = arr[j];
                break;
            }
        }
    }

    cin.ignore(32767, '\n');

    cout << "Массив сформирован (search_flight_btc)" << endl;
}

void rpl_typefl_from_file(string path, airplane arr[], int size) {
    /* Замена типа полета через данные в файле
     * path (string): путь к файлу
     * arr[] (airplane): массив, в котором будут заменяться значения
     * size (int): размерность массива
     */

    ifstream file;
    file.open(path);

    string line[3];

    if (file.is_open()) {
        while (!file.eof()) {
            file >> line[0] >> line[1] >> line[2];

            for (int i = 0; i < size; i++) {
                if (line[0] == arr[i].arrive_point) {
                    arr[i].type_flight = line[1];
                }
            }
        }
    }

    file.close();
    cout << "Корректировка типов полета выполнена." << endl;
}

void wr_bin_file(string path, airplane arr[], int size) {
    /* Запись в бинарный файл */

    ofstream file(path, ios::out | ios::binary);

    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            size_t lenstring = arr[i].arrive_point.size();
            file.write((char*)&lenstring, sizeof(lenstring));
            file.write(arr[i].arrive_point.c_str(), lenstring);

            file.write((char*)&arr[i].t_go, sizeof(timeap));
            file.write((char*)&arr[i].t_end, sizeof(timeap));
            file.write((char*)&arr[i].t_trip, sizeof(timeap));
            file.write((char*)&arr[i].cost, sizeof(arr[i].cost));

            size_t lenstring1 = arr[i].type_flight.size();
            file.write((char*)&lenstring1, sizeof(lenstring1));
            file.write(arr[i].type_flight.c_str(), lenstring1);
        }
    }
    file.close();
    cout << "Файл записан." << endl;
}

void rd_bin_file(string path, airplane arr[], int size) {
    /* Чтение бинарного файла  */
    fstream file(path, ios::in | ios::binary);

    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            size_t lenstring;
            file.read((char*)&lenstring, sizeof(lenstring));
            arr[i].arrive_point.resize(lenstring);
            file.read(&arr[i].arrive_point[0], lenstring);

            file.read((char*)&arr[i].t_go, sizeof(timeap));
            file.read((char*)&arr[i].t_end, sizeof(timeap));
            file.read((char*)&arr[i].t_trip, sizeof(timeap));
            file.read((char*)&arr[i].cost, sizeof(arr[i].cost));

            size_t lenstring1;
            file.read((char*)&lenstring1, sizeof(lenstring1));
            arr[i].type_flight.resize(lenstring1);
            file.read(&arr[i].type_flight[0], lenstring1);
        }
    }

    file.close();
    cout << "Файл прочитан." << endl;

}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    airplane airplanes[20];

    airplanes[0] = {"Москва", {8, 0, 0}, {10, 30, 0}, {2, 30, 0}, 15000.5, "чартер"};
    airplanes[1] = {"Стамбул", {10, 15, 0}, {14, 45, 0}, {4, 30, 0}, 23500.0, "стыковка"};
    airplanes[2] = {"Волгоград", {6, 30, 0}, {13, 20, 0}, {6, 50, 0}, 45800.0, "стыковка"};
    airplanes[3] = {"Сочи", {9, 0, 0}, {11, 15, 0}, {2, 15, 0}, 8900.75, "чартер"};
    airplanes[4] = {"Нью-Йорк", {5, 45, 0}, {18, 30, 0}, {12, 45, 0}, 125000.0, "транзит"};
    airplanes[5] = {"Париж", {11, 0, 0}, {16, 45, 0}, {5, 45, 0}, 38900.0, "стыковка"};
    airplanes[6] = {"Калининград", {7, 30, 0}, {9, 45, 0}, {2, 15, 0}, 12500.0, "транзит"};
    airplanes[7] = {"Дубай", {13, 20, 0}, {18, 10, 0}, {4, 50, 0}, 32500.5, "транзит"};
    airplanes[8] = {"Токио", {2, 0, 0}, {22, 30, 0}, {20, 30, 0}, 185000.0, "стыковка"};
    airplanes[9] = {"Симферополь", {8, 45, 0}, {10, 50, 0}, {2, 5, 0}, 7500.0, "чартер"};
    airplanes[10] = {"Рим", {9, 30, 0}, {13, 45, 0}, {4, 15, 0}, 28900.0, "транзит"};
    airplanes[11] = {"Бангкок", {4, 0, 0}, {21, 30, 0}, {17, 30, 0}, 67800.0, "стыковка"};
    airplanes[12] = {"Казань", {12, 0, 0}, {13, 40, 0}, {1, 40, 0}, 4900.0, "чартер"};
    airplanes[13] = {"Белград", {7, 15, 0}, {11, 30, 0}, {4, 15, 0}, 31200.0, "транзит"};
    airplanes[14] = {"Сидней", {1, 30, 0}, {23, 45, 0}, {22, 15, 0}, 245000.0, "стыковка"};
    airplanes[15] = {"Анапа", {14, 0, 0}, {16, 10, 0}, {2, 10, 0}, 8200.0, "чартер"};
    airplanes[16] = {"Берлин", {10, 45, 0}, {13, 55, 0}, {3, 10, 0}, 19500.0, "транзит"};
    airplanes[17] = {"Шанхай", {3, 0, 0}, {20, 30, 0}, {17, 30, 0}, 158000.0, "стыковка"};
    airplanes[18] = {"Екатеринбург", {11, 30, 0}, {13, 45, 0}, {2, 15, 0}, 6800.0, "чартер"};
    airplanes[19] = {"Кировград", {8, 0, 0}, {12, 20, 0}, {4, 20, 0}, 27500.0, "транзит"};

    filt_time_arr(airplanes, 20);

    for(int i = 0; i < std::size(airplanes); i++) {
        print_flight(airplanes[i]);
    }

    cout << "------------------------------------------------------------------" << endl;

    airplane new_flight[20];
    search_grad(airplanes, new_flight, 20);
    for(int i = 0; i < std::size(airplanes); i++) {
        print_flight(new_flight[i]);
    }

    cout << "------------------------------------------------------------------" << endl;

    search_flight_by_name(airplanes, 20);

    cout << "------------------------------------------------------------------" << endl;

    print_flights_by_tt(airplanes, 20);

    cout << "------------------------------------------------------------------" << endl;

    airplane airbus;
    airbus.arrive_point = "Москва";
    airbus.t_go.hour = 12;
    airbus.t_go.min = 0;
    airbus.t_go.sec = 0;
    airbus.t_end.hour = 13;
    airbus.t_end.min = 0;
    airbus.t_end.sec = 0;
    airbus.t_trip.hour = 1;
    airbus.t_trip.min = 0;
    airbus.t_trip.sec = 0;
    airbus.cost = 1000;
    airbus.type_flight = "транзит";
    rename_flight(airbus);
    print_flight(airbus);

    cout << "------------------------------------------------------------------" << endl;

    search_flight_btc(airplanes, 20, new_flight);
    for(int i = 0; i < std::size(airplanes); i++){
        print_flight(new_flight[i]);
    }

    cout << "------------------------------------------------------------------" << endl;

    search_flight_by_name(airplanes, 20);

    cout << "------------------------------------------------------------------" << endl;

    rpl_typefl_from_file("text.txt", airplanes, 20);

    for (int i = 0; i < 20; i++) {
        print_flight(airplanes[i]);
    }

    cout << "------------------------------------------------------------------" << endl;

    wr_bin_file("textbinary.txt", airplanes, 20);

    airplane new_airplane[20];

    cout << "------------------------------------------------------------------" << endl;

    rd_bin_file("textbinary.txt", new_airplane, 20);

    for (int i = 0; i < 20; i++) {
        print_flight(new_airplane[i]);
    }

    system("pause");
    return 0;
}
