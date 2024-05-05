#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        std::cout << "Error 404" << std::endl;
        return 1;
    }

    std::vector<int> vector;
    int num;
    while (inputFile >> num) {
        vector.push_back(num);
    }

    // Реверсируем последовательность элементов вектора
    std::reverse(vector.begin(), vector.end());

    // Находим минимальный элемент
    int minElement = *std::min_element(vector.begin(), vector.end());
    std::cout << "Min elem: " << minElement << std::endl;

    // Удаляем из вектора все четные элементы
    vector.erase(std::remove_if(vector.begin(), vector.end(), [](int n) { return n % 2 == 0; }), vector.end());

    // Сортируем вектор в возрастающей последовательности
    std::sort(vector.begin(), vector.end());

    // Вставляем произвольный элемент в вектор
    int newElement = 25;
    vector.insert(std::upper_bound(vector.begin(), vector.end(), newElement), newElement);

    // Определяем индекс заданного элемента
    int elementToFind = 3;
    auto it = std::find(vector.begin(), vector.end(), elementToFind);
    if (it != vector.end()) {
        int index = std::distance(vector.begin(), it);
        std::cout << "Index element " << elementToFind << " after all operations: " << index << std::endl;
    }
    else {
        std::cout << "Element not found after all operations" << std::endl;
    }

    // Удаляем дублированные элементы
    vector.erase(std::unique(vector.begin(), vector.end()), vector.end());

    // Выводим обновленный вектор
    std::cout << "Updated vector: ";
    for (int elem : vector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    inputFile.close();
    return 0;
}