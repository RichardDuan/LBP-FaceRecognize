#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
struct IntNode {
    int data;
    IntNode* next;
    IntNode(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    IntNode* front;
    IntNode* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int value) {  //value入列
        IntNode* newNode = (IntNode*)malloc(sizeof(IntNode));
        if (newNode == nullptr) {
            exit(EXIT_FAILURE);
        }
        newNode->data = value;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {   //元素出列，并返回出列的值
        if (front == nullptr) {
            exit(EXIT_FAILURE);
        }

        int value = front->data;
        IntNode* temp = front;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }

        free(temp);
        return value;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    // 获取队列中第i个位置的元素
    int getAtIndex(int i) {
        IntNode* current = front;
        int currentIndex = 0;

        while (current != nullptr && currentIndex < i) {
            current = current->next;
            currentIndex++;
        }

        if (current == nullptr || currentIndex > i) {
            exit(EXIT_FAILURE);
        }

        return current->data;
    }
};