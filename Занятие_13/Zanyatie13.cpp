#include <iostream>

using namespace std;


template <class Atype>
class Array {
     Atype* array;
     int size;

public:
     Array(int size = 1) {
          size = size > 0 ? size : 1;

          array = new Atype[size];

          this->size = size;
     }

     Atype& operator [](int index) {
          return array[index];
     }

     int operator()() {
          return size;
     }

     void add(Atype elem) {
          Atype* new_array = new Atype[size + 1];

          for (int i = 0; i < size; i++) {
               new_array[i] = array[i];
          }

          new_array[size] = elem;

          delete[] array;
          array = new_array;

          size++;
     }

     void remove(Atype elem) {
          Atype* new_array = new Atype[size - 1];

          bool flag = false;

          for (int i = 0; i < size - 1; i++) {
               if (array[i] != elem && flag == false) {
                    new_array[i] = array[i];
               }
               else if (array[i] == elem && flag == false){
                    flag = true;

                    new_array[i] = array[i+1];
               }
               else if (flag == true) {
                    new_array[i] = array[i+1];
               }
          }

          delete [] array;

          array = new_array;

          size--;
     }

     void sort(int reverse = 0) {
          Atype t;

          if (reverse == 0) {
               for (int i = 0; i < size; i++) {
                    for (int j = size - 1; j > i; j--) {
                         if (array[j - 1] > array[j]) {
                              t = array[j - 1];

                              array[j - 1] = array[j];
                              array[j] = t;
                         }
                    }
               }
          }
          else if (reverse == 1) {
               for (int i = 0; i < size; i++) {
                    for (int j = size - 1; j > i; j--) {
                         if (array[j - 1] < array[j]) {
                              t = array[j - 1];

                              array[j - 1] = array[j];
                              array[j] = t;
                         }
                    }
               }
          }
     }

     void del() {
          delete[] array;

          array = nullptr;

          size = 0;
     }

     ~Array() {
          del();
     }
};

class El_Device {
     string brand;
     float weight;
     int memory;

     static float sum_memory;
     static int count_of_devices;

public:
     El_Device(string brand, float weight, int memory) {
          this->brand = brand;
          this->weight = weight;
          this->memory = memory;


          sum_memory += memory;
          count_of_devices++;
     }

     friend float calc_av_mem();

     virtual void show() {
          cout << "Производитель: " << brand << endl;
          cout << "Вес: " << weight << endl;
          cout << "Количество памяти (ГБ): " << memory << endl;
     }

     int get_memory() {
          return memory;
     }

     string get_brand() {
          return brand;
     }

     virtual void update(int memory = 0) {
          if (memory > 0) {
               this->memory = memory;
               sum_memory+= memory;
          };
     }

     ~El_Device() {
          sum_memory -= memory;
          count_of_devices--;
     }

     void destroy() {
          cout << "Устройство уничтожено" << endl;

          sum_memory -= memory;
          count_of_devices--;
     }
};

class PC: public El_Device {
    int videomemory;
    float GHz_CPU;
    int count_cores;

public:
     PC(string brand, float weight, int memory, int videomemory, float ghz_cpu, int count_cores): El_Device(brand, weight, memory) {
        this->videomemory = videomemory;
        this->GHz_CPU = ghz_cpu;
        this->count_cores = count_cores;
    }

     void show() {
        El_Device::show();
        cout << "Процессор: " << GHz_CPU << "GHz. " << "Количество ядер: " << count_cores << endl;
        cout << "Видеопамять: " << videomemory << endl;
    }

     void update(int memory = 0, int videomemory = 0, float ghz_cpu = 0, int count_cores = 0) {
          El_Device::update(memory);

          if (videomemory > 0) {
               this->videomemory = videomemory;
          }

          if (ghz_cpu > 0) {
               this->GHz_CPU = ghz_cpu;
          }

          if (count_cores > 0) {
               this->count_cores = count_cores;
          }
     }
};

float calc_av_mem() {
     return El_Device::sum_memory/El_Device::count_of_devices;
}

template<class Eltype>
class El_Array {
     Eltype* array;
     int size;

public:
     El_Array(int size) {
          size = size > 0 ? size : 1;

          array = new Eltype[size];

          for (int i = 0; i < size; i++) {
               array[i] = nullptr;
          }

          this->size = size;
     }

     Eltype& operator [](int index) {
          return array[index];
     }

     int len() {
          return size;
     }

     void add(Eltype elem) {
          Eltype* new_array = new Eltype[size + 1];

          for (int i = 0; i < size; i++) {
               new_array[i] = array[i];
          }

          new_array[size] = elem;

          delete[] array;
          array = new_array;

          size++;
     }

     void remove(Eltype elem) {
          Eltype* new_array = new Eltype[size - 1];

          bool flag = false;
          for (int i = 0; i < size - 1; i++) {
               if (array[i] != elem && flag == false) {
                    new_array[i] = array[i];
               }
               else if (array[i] == elem && flag == false){
                    flag = true;

                    new_array[i] = array[i+1];
               }
               else if (flag == true) {
                    new_array[i] = array[i+1];
               }
          }

          delete [] array;
          array = new_array;
          size--;
     }


     void remove(string brand) {
          Eltype* new_array = new Eltype[size - 1];

          bool flag = false;
          for (int i = 0; i < size - 1; i++) {
               if (array[i]->get_brand() != brand && flag == false) {
                    new_array[i] = array[i];
               }
               else if (array[i]->get_brand() == brand && flag == false){
                    flag = true;

                    new_array[i] = array[i+1];
               }
               else if (flag == true) {
                    new_array[i] = array[i+1];
               }
          }

          delete [] array;
          array = new_array;
          size--;
     }

     void mem_sort(int reverse = 0) {
          Eltype t;

          if (reverse == 0) {
               for (int i = 0; i < size; i++) {
                    for (int j = size - 1; j > i; j--) {
                         if (array[j - 1]->get_memory() > array[j]->get_memory()) {
                              t = array[j - 1];

                              array[j - 1] = array[j];
                              array[j] = t;
                         }
                    }
               }
          }
          else if (reverse == 1) {
               for (int i = 0; i < size; i++) {
                    for (int j = size - 1; j > i; j--) {
                         if (array[j - 1]->get_memory() < array[j]->get_memory()) {
                              t = array[j - 1];

                              array[j - 1] = array[j];
                              array[j] = t;
                         }
                    }
               }
          }
     }

     void del() {
          delete[] array;

          array = nullptr;

          size = 0;
     }

     ~El_Array() {
          del();
     }
};

int El_Device::count_of_devices;
float El_Device::sum_memory;

int main() {
//      Array<int> a(4);
//      a[0] = 7; a[1] = 4; a[2] = 10; a[3] = 1;
//
//      for (int i = 0; i < a(); i++) {
//           cout << a[i] << endl;
//      }
//
//
//      a.del();

     // PC a("ASUS", 3, 512, 4, 3.5, 4);
     // a.show();
     // cout << calc_av_mem() << endl;
     // cout << "---" << endl;
     // a.update(1024, -1, 4, 2);
     // cout << "---" << endl;
     // a.show();
     // cout << "---" << endl;
     // a.destroy();
     // cout << calc_av_mem() << endl;


     El_Array<El_Device*> b(3);

     b[0] = new PC("Acer", 2, 256, 2, 1.7, 2);
     b[1] = new PC("ASUS", 3, 1024, 4, 2, 4);
     b[2] = new PC("HP", 1.5, 512, 1, 2, 1);

     PC* comp = new PC("HONOR", 1, 128, 1, 2, 2);
     b.add(comp);
     b.remove("Acer");
     b.mem_sort();

     for (int i = 0; i < b.len(); i++) {
          cout << b[i]->get_memory() << endl;
     }





     return 0;
}