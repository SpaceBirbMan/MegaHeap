#pragma once
#include <iostream>
#include <vector>
#include <cassert>

/// ����� Heap ������������ ����� MaxHeap (������������ �������� ����)
/// ���� � ��� ��������� ������, ������� ������������ �������� ������.
/// ������ ���� ����� �� ����� ���� ��������, � �������� ���� ������
/// ������ �������� ��� �������� (��� MaxHeap).
class Heap {
public:
    Heap() {}

    /// ������� �������� � ����, ��������� O(log n)
    /// ����� ������� ����������� � ����� � ����������� ����� ���
    /// �������������� �������� ����.
    void push(int value) {
        data.push_back(value); // ��������� ����� ������� � ����� �������
        heapifyUp(data.size() - 1); // ��������������� ��������� ���� ����� �����
    }

    /// �������� ����� (������������� �������� ��� MaxHeap), ��������� O(log n)
    /// ������� ����� ���������� ��������� ���������, � �����������������
    /// ��������� ���� ������� ������ ����.
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
    int top() const {
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
    /// ���������� true, ���� ������� ������, ����� false.
    bool find(int value) const {
        for (const int& element : data) {
            if (element == value) {
                return true;
            }
        }
        return false;

        // ����� find ��������� �������� ����� �� ������� data, 
        // ��������, ���� �� � ���� ��������� ������� value.
        // ���� ������ ��������, ��� ��� �������� 
        // � �������� ���� �� ����������� �������.
    }

private:
    std::vector<int> data; // ������ ��� �������� ��������� ����

    /// �������������� ��������� ���� ����� ����� (up-heapify), ��������� O(log n)
    /// ���� ����� ������� �������� �������, �� ����������� ����� ��
    /// ���������� ���������� �������.
    void heapifyUp(int index) {
        while (index > 0 && data[parent(index)] < data[index]) {
            std::cout << "heapifyUp: swapping " << data[parent(index)] << " and " << data[index] << "\n";
            std::swap(data[parent(index)], data[index]);
            index = parent(index);
        }
    }

    /// �������������� ��������� ���� ������ ���� (down-heapify), ��������� O(log n)
    /// ���� ������ �������� �������, �� ���������� ����, ���� �� ������ �� �����.
    void heapifyDown(int index) {
        while (true) {
            int maxIndex = index;
            int leftChildIndex = leftChild(index);
            int rightChildIndex = rightChild(index);

            // ��������� ����� �������� ����
            if (leftChildIndex < data.size() && data[leftChildIndex] > data[maxIndex]) {
                maxIndex = leftChildIndex;
            }

            // ��������� ������ �������� ����
            if (rightChildIndex < data.size() && data[rightChildIndex] > data[maxIndex]) {
                maxIndex = rightChildIndex;
            }

            // ���� ������� �������, ������ ������� � ���������� ��������
            if (index != maxIndex) {
                std::cout << "heapifyDown: swapping " << data[index] << " and " << data[maxIndex] << "\n";
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

    // ���������� ������ ������ �������
    int leftChild(int index) const {
        return 2 * index + 1;
    }

    /// ���������� ������ ������� �������
    int rightChild(int index) const {
        return 2 * index + 2;
    }
};
