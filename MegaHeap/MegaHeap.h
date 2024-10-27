#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm> // ��� std::reverse
#include <stdexcept> // ��� std::runtime_error
#include <type_traits> // ��� std::enable_if

/// ����� Heap ������������ ����� MaxHeap (������������ �������� ����)
/// ���� � ��� ��������� ������, ������� ������������ �������� ������.
/// ������ ���� ����� �� ����� ���� ��������, � �������� ���� ������
/// ������ �������� ��� �������� (��� MaxHeap).
template <typename T>
class Heap {
    static_assert(std::is_arithmetic<T>::value, "Heap can only be instantiated with arithmetic types.");

public:
    // �����������, ����������� ������ ��� ������������� ����
    Heap(const std::vector<T>& elements) {
        for (const T& element : elements) {
            push(element); // ������� ��������� � ����
        }
    }

    Heap() {}

    /// ������� �������� � ����, ��������� O(log n)
    void push(T value) {
        data.push_back(value); // ��������� ����� ������� � ����� �������
        heapifyUp(data.size() - 1); // ��������������� ��������� ���� ����� �����
    }

    /// �������� ����� (������������� �������� ��� MaxHeap), ��������� O(log n)
    void pop() {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty!");
        }
        data[0] = data.back(); // �������� ������ ��������� ���������
        data.pop_back(); // ������� ��������� �������
        if (!data.empty()) {
            heapifyDown(0); // ��������������� ��������� ���� ������ ����
        }
    }

    /// ��������� ������������� �������� (��� MaxHeap)
    T top() const {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty!");
        }
        return data[0]; // ������ � ������������ �������
    }

    /// ��������, ����� �� ����
    bool empty() const {
        return data.empty();
    }

    /// ���������� ������ ����
    size_t size() const {
        return data.size();
    }

    void clear() {
        data.clear();
    }

    /// ����� �������� � ����
    bool find(const T& value) const {
        for (const T& element : data) {
            if (element == value) {
                return true;
            }
        }
        return false;
    }

    /// ���������� � �������������� ����
    static std::vector<T> sort(const std::vector<T>& d) {
        Heap heap(d); // ������ ���� �� ������� ������
        std::vector<T> sorted;

        while (!heap.empty()) {
            sorted.push_back(heap.top()); // �������� ������������ �������
            heap.pop(); // ������� ��� �� ����
        }
        return sorted; // ���������� ��������������� ������
    }

private:
    std::vector<T> data; // ������ ��� �������� ��������� ����

    /// �������������� ��������� ���� ����� �����
    void heapifyUp(int index) {
        while (index > 0 && data[parent(index)] < data[index]) {
            std::swap(data[parent(index)], data[index]);
            index = parent(index);
        }
    }

    /// �������������� ��������� ���� ������ ����
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
                break;  // ��������� ����, ���� ������� ������������
            }
        }
    }

    /// ���������� ������ ��������
    int parent(int index) const {
        return (index - 1) / 2;
    }

    /// ���������� ������ ������ �������
    int leftChild(int index) const {
        return 2 * index + 1;
    }

    /// ���������� ������ ������� �������
    int rightChild(int index) const {
        return 2 * index + 2;
    }
};
