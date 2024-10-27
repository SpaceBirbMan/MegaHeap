#pragma once
#include <iostream>
#include <vector>
#include <cassert>

/// Класс Heap представляет собой MaxHeap (максимальную бинарную кучу)
/// Куча — это структура данных, которая поддерживает свойства дерева.
/// Каждый узел имеет не более двух потомков, а значение узла всегда
/// больше значений его потомков (для MaxHeap).
class Heap {
public:
    Heap() {}

    /// Вставка элемента в кучу, сложность O(log n)
    /// Новый элемент добавляется в конец и поднимается вверх для
    /// восстановления свойства кучи.
    void push(int value) {
        data.push_back(value); // Добавляем новый элемент в конец массива
        heapifyUp(data.size() - 1); // Восстанавливаем структуру кучи снизу вверх
    }

    /// Удаление корня (максимального элемента для MaxHeap), сложность O(log n)
    /// Элемент корня заменяется последним элементом, и восстанавливается
    /// структура кучи методом спуска вниз.
    void pop() {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty!");
        }
        data[0] = data.back(); // Заменяем корень последним элементом
        data.pop_back(); // Убираем последний элемент
        if (!data.empty()) {
            heapifyDown(0); // Восстанавливаем структуру кучи сверху вниз
        }
    }

    /// Получение максимального элемента (для MaxHeap)
    int top() const {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty!");
        }
        return data[0]; // Корень — максимальный элемент
    }

    /// Проверка, пуста ли куча
    bool empty() const {
        return data.empty();
    }

    /// Возвращает размер кучи
    size_t size() const {
        return data.size();
    }

    void clear() {
        data.clear();
    }

    /// Поиск элемента в куче
    /// Возвращает true, если элемент найден, иначе false.
    bool find(int value) const {
        for (const int& element : data) {
            if (element == value) {
                return true;
            }
        }
        return false;

        // Метод find выполняет линейный поиск по вектору data, 
        // проверяя, есть ли в куче указанный элемент value.
        // Этот подход оправдан, так как элементы 
        // в бинарной куче не упорядочены линейно.
    }

private:
    std::vector<int> data; // Вектор для хранения элементов кучи

    /// Восстановление структуры кучи снизу вверх (up-heapify), сложность O(log n)
    /// Если новый элемент нарушает порядок, он поднимается вверх до
    /// достижения правильной позиции.
    void heapifyUp(int index) {
        while (index > 0 && data[parent(index)] < data[index]) {
            std::cout << "heapifyUp: swapping " << data[parent(index)] << " and " << data[index] << "\n";
            std::swap(data[parent(index)], data[index]);
            index = parent(index);
        }
    }

    /// Восстановление структуры кучи сверху вниз (down-heapify), сложность O(log n)
    /// Если корень нарушает порядок, он опускается вниз, пока не станет на место.
    void heapifyDown(int index) {
        while (true) {
            int maxIndex = index;
            int leftChildIndex = leftChild(index);
            int rightChildIndex = rightChild(index);

            // Проверяем левый дочерний узел
            if (leftChildIndex < data.size() && data[leftChildIndex] > data[maxIndex]) {
                maxIndex = leftChildIndex;
            }

            // Проверяем правый дочерний узел
            if (rightChildIndex < data.size() && data[rightChildIndex] > data[maxIndex]) {
                maxIndex = rightChildIndex;
            }

            // Если порядок нарушен, меняем местами и продолжаем проверку
            if (index != maxIndex) {
                std::cout << "heapifyDown: swapping " << data[index] << " and " << data[maxIndex] << "\n";
                std::swap(data[index], data[maxIndex]);
                index = maxIndex;
            }
            else {
                break;  // Завершаем цикл, если порядок восстановлен
            }
        }
    }

    /// Возвращает индекс родителя
    int parent(int index) const {
        return (index - 1) / 2;
    }

    // Возвращает индекс левого потомка
    int leftChild(int index) const {
        return 2 * index + 1;
    }

    /// Возвращает индекс правого потомка
    int rightChild(int index) const {
        return 2 * index + 2;
    }
};
