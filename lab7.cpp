#include <iostream>
#include <vector>
#include <list>
#include <ctime>

int main() {
    setlocale(LC_ALL, "Russian");
    // Создание векторов и списков
    std::vector<int> vector;
    std::list<int> list;

    // Замер времени вставки элементов в вектор
    clock_t start_time = clock();
    for (int i = 0; i < 100000; i++) {
        vector.push_back(i);
    }
    clock_t end_time = clock();
    double vector_insert_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Замер времени вставки элементов в список
    start_time = clock();
    for (int i = 0; i < 100000; i++) {
        list.push_back(i);
    }
    end_time = clock();
    double list_insert_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Вывод результатов
    std::cout << "Время вставки в вектор: " << vector_insert_time << " секунд" << std::endl;
    std::cout << "Время вставки в список: " << list_insert_time << " секунд" << std::endl;

    std::vector<int> vector_small(1000);
    std::vector<int> vector_medium(10000);
    std::vector<int> vector_large(100000);

  
    std::list<int> list_small(1000);
    std::list<int> list_medium(10000);
    std::list<int> list_large(100000);


    // Вывод информации о занимаемой памяти
    std::cout << "Размер | Вектор | Список" << std::endl;
    std::cout << "-------| -------| --------" << std::endl;
    std::cout << "1000   |   " << sizeof(vector_small) << "   |   " << sizeof(list_small) << std::endl;
    std::cout << "10000  |   " << sizeof(vector_medium) << "   |   " << sizeof(list_medium) << std::endl;
    std::cout << "100000 |   " << sizeof(vector_large) << "   |   " << sizeof(list_large) << std::endl;


    return 0;
}
