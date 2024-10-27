#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "MegaHeap.h"

using namespace std;

void testHeap() {
    Heap heap;

    // ����: ������ ����
    assert(heap.empty());
    assert(heap.size() == 0);

    // ����: ������� ������ ��������
    heap.push(10);
    assert(!heap.empty());
    assert(heap.size() == 1);
    assert(heap.top() == 10);
    assert(heap.find(10) == true);
    assert(heap.find(5) == false); // ����� ��������, �������� ���

    // ����: ������� ���������� ���������
    heap.push(20);
    heap.push(5);
    heap.push(30);
    assert(heap.size() == 4);
    assert(heap.top() == 30); // MaxHeap, ������� ������������ ������� ������ ���� 30
    assert(heap.find(20) == true);
    assert(heap.find(100) == false); // ����� ��������������� ��������

    // ����: �������� ������������� ��������
    heap.pop();
    assert(heap.top() == 20); // 30 ������, ������ ������������ 20

    // ����: ������� � �������� ������������� ���������
    heap.push(20);
    heap.push(20);
    assert(heap.size() == 5);
    assert(heap.top() == 20); // �� ������� ������ ���������� 20
    heap.pop();
    assert(heap.top() == 20); // ������� ���� �� 20
    heap.pop();
    assert(heap.top() == 20);
    heap.pop();
    assert(heap.find(20) == false); // ����� �������� ���� 20-�� �� ������ ��� � ����

    // ����: ������� ������������� �����
    heap.clear();
    heap.push(-10);
    assert(heap.top() == -10); // ������� -10

    heap.push(-20);
    assert(heap.top() == -10); // ������� �������� -10, ��� ��� ��� MaxHeap

    heap.push(-5);
    assert(heap.top() == -5); // ������ �� ������� -5, ��� ��� ��� ������������ �������

    heap.push(-15);
    assert(heap.top() == -5); // ������� �������� -5


    // ����: ������� ���������� ������������� � ������������� ��������
    heap.push(15);
    heap.push(-10);
    heap.push(15);
    assert(heap.top() == 15); // �� ������� ������ ���� 15, ��������� ��� MaxHeap

    // ����: �������� ���� ���������
    while (!heap.empty()) {
        heap.pop();
    }
    assert(heap.empty());

    // ����: �������� �� ������ ���� (������� ����������)
    bool caught = false;
    try {
        heap.pop();
    }
    catch (const std::runtime_error& e) {
        caught = true;
    }
    assert(caught);  // ���������� ������ ���� �������

    // ����: ������-����
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

    // ����: ������������ ���� � ������� ����������
    vector<int> testValues = { 100, 50, 70, -40, -5, 15, 95, -30 };
    for (int val : testValues) {
        heap.push(val);
    }
    assert(heap.top() == 100); // ����� ������� ����� � 100
    for (int val : testValues) {
        assert(heap.find(val) == true); // ��� �������� ������ ���� �������
    }
    heap.pop(); // ������� 100
    assert(heap.top() == 95); // ������ ������� � 95

    // �������� ����� ���� pop
    while (!heap.empty()) {
        heap.pop();
    }
    assert(heap.empty());
}

int main() {
    testHeap();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
