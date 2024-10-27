#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "MegaHeap.h"

using namespace std;

void testHeap() {
    Heap<int> heap; // Указываем тип int

    // Тест: Пустая куча
    assert(heap.empty());
    assert(heap.size() == 0);

    // Тест: Вставка одного элемента
    heap.push(10);
    assert(!heap.empty());
    assert(heap.size() == 1);
    assert(heap.top() == 10);
    assert(heap.find(10) == true);
    assert(heap.find(5) == false); // Поиск элемента, которого нет

    // Тест: Вставка нескольких элементов
    heap.push(20);
    heap.push(5);
    heap.push(30);
    assert(heap.size() == 4);
    assert(heap.top() == 30); // MaxHeap, поэтому максимальный элемент должен быть 30
    assert(heap.find(20) == true);
    assert(heap.find(100) == false); // Поиск несуществующего элемента

    // Тест: Удаление максимального элемента
    heap.pop();
    assert(heap.top() == 20); // 30 удален, теперь максимальный 20

    // Тест: Вставка и удаление повторяющихся элементов
    heap.push(20);
    heap.push(20);
    assert(heap.size() == 5);
    assert(heap.top() == 20); // На вершине должно оставаться 20
    heap.pop();
    assert(heap.top() == 20); // Остался один из 20
    heap.pop();
    assert(heap.top() == 20);
    heap.pop();
    assert(heap.find(20) == false); // После удаления всех 20-ок их больше нет в куче

    // Тест: Вставка отрицательных чисел
    heap.clear();
    heap.push(-10);
    assert(heap.top() == -10); // Вершина -10

    heap.push(-20);
    assert(heap.top() == -10); // Вершина остается -10, так как это MaxHeap

    heap.push(-5);
    assert(heap.top() == -5); // Теперь на вершине -5, так как это максимальный элемент

    heap.push(-15);
    assert(heap.top() == -5); // Вершина остается -5

    // Тест: Вставка одинаковых положительных и отрицательных значений
    heap.push(15);
    heap.push(-10);
    heap.push(15);
    assert(heap.top() == 15); // На вершине должно быть 15, поскольку это MaxHeap

    // Тест: Удаление всех элементов
    while (!heap.empty()) {
        heap.pop();
    }
    assert(heap.empty());

    // Тест: Удаление из пустой кучи (ожидаем исключение)
    bool caught = false;
    try {
        heap.pop();
    }
    catch (const std::runtime_error& e) {
        caught = true;
    }
    assert(caught);  // Исключение должно быть поймано

    // Тест: Стресс-тест
    for (int i = 0; i < 1000; ++i) {
        heap.push(i);
    }
    assert(heap.size() == 1000);
    assert(heap.top() == 999);

    for (int i = 999; i >= 0; --i) {
        assert(heap.top() == i);
        heap.pop();
    }
    assert(heap.empty());

    // Тест: Переполнение кучи с разными значениями
    vector<int> testValues = { 100, 50, 70, -40, -5, 15, 95, -30 };
    for (int val : testValues) {
        heap.push(val);
    }
    assert(heap.top() == 100); // Самое большое число — 100
    for (int val : testValues) {
        assert(heap.find(val) == true); // Все значения должны быть найдены
    }
    heap.pop(); // Убираем 100
    assert(heap.top() == 95); // Теперь вершина — 95

    // Проверка после всех pop
    while (!heap.empty()) {
        heap.pop();
    }
    assert(heap.empty());
}

void testHeapSort() {
    // Тест 1: Пустая куча
    assert(Heap<int>::sort({}).empty());

    // Тест 2: Один элемент
    assert(Heap<int>::sort({ 5 }) == std::vector<int>{5});

    // Тест 3: Два элемента
    std::vector<int> a = std::vector<int>{ 10, 5 };
    assert(Heap<int>::sort({ 5, 10 }) == a);

    // Тест 4: Упорядоченный массив
    a = std::vector<int>{ 10, 8, 5, 3 };
    assert(Heap<int>::sort({ 3, 8, 5, 10 }) == a);

    // Тест 5: Неупорядоченный массив
    a = std::vector<int>{ 5, 4, 3, 2, 1 };
    assert(Heap<int>::sort({ 4, 1, 3, 2, 5 }) == a);

    // Тест 6: Повторяющиеся элементы
    a = std::vector<int>{ 7, 7, 7, 5, 3 };
    assert(Heap<int>::sort({ 7, 7, 3, 7, 5 }) == a);

    // Тест 7: Отрицательные числа
    a = std::vector<int>{ -1, -2, -3 };
    assert(Heap<int>::sort({ -1, -3, -2 }) == a);

    // Тест 8: Большой массив
    std::vector<int> largeArray;
    for (int i = 100; i >= 1; --i) {
        largeArray.push_back(i);
    }
    auto sorted = Heap<int>::sort(largeArray);
    for (int i = 0; i < 100; ++i) {
        assert(sorted[i] == 100 - i);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    testHeapSort();
    testHeap();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
