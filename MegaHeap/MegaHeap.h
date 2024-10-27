#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm> // для std::reverse
#include <stdexcept> // для std::runtime_error
#include <type_traits> // для std::enable_if

/// Класс Heap представляет собой MaxHeap (максимальную бинарную кучу)
/// Куча — это структура данных, которая поддерживает свойства дерева.
/// Каждый узел имеет не более двух потомков, а значение узла всегда
/// больше значений его потомков (для MaxHeap).
template <typename T>
class Heap {
    static_assert(std::is_arithmetic<T>::value, "Heap can only be instantiated with arithmetic types.");

public:
    // Конструктор, принимающий вектор для инициализации кучи
    Heap(const std::vector<T>& elements) {
        for (const T& element : elements) {
            push(element); // Вставка элементов в кучу
        }
    }

    Heap() {}

    /// Вставка элемента в кучу, сложность O(log n)
    void push(T value) {
        data.push_back(value); // Добавляем новый элемент в конец массива
        heapifyUp(data.size() - 1); // Восстанавливаем структуру кучи снизу вверх
    }

    /// Удаление корня (максимального элемента для MaxHeap), сложность O(log n)
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
    T top() const {
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
    bool find(const T& value) const {
        for (const T& element : data) {
            if (element == value) {
                return true;
            }
        }
        return false;
    }

    /// Сортировка с использованием кучи
    static std::vector<T> sort(const std::vector<T>& d) {
        Heap heap(d); // Создаём кучу из входных данных
        std::vector<T> sorted;

        while (!heap.empty()) {
            sorted.push_back(heap.top()); // Получаем максимальный элемент
            heap.pop(); // Удаляем его из кучи
        }
        return sorted; // Возвращаем отсортированный вектор
    }

private:
    std::vector<T> data; // Вектор для хранения элементов кучи

    /// Восстановление структуры кучи снизу вверх
    void heapifyUp(int index) {
        while (index > 0 && data[parent(index)] < data[index]) {
            std::swap(data[parent(index)], data[index]);
            index = parent(index);
        }
    }

    /// Восстановление структуры кучи сверху вниз
    void heapifyDown(int index) {
        while (true) {
            int maxIndex = index;
            int leftChildIndex = leftChild(index);
            int rightChildIndex = rightChild(index);

            if (leftChildIndex < data.size() && data[leftChildIndex] > data[maxIndex]) {
                maxIndex = leftChildIndex;
            }

            if (rightChildIndex < data.size() && data[rightChildIndex] > data[maxIndex]) {
                maxIndex = rightChildIndex;
            }

            if (index != maxIndex) {
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

    /// Возвращает индекс левого потомка
    int leftChild(int index) const {
        return 2 * index + 1;
    }

    /// Возвращает индекс правого потомка
    int rightChild(int index) const {
        return 2 * index + 2;
    }
};
