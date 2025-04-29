#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedStack {
public:
    LinkedStack() : top(nullptr) {}

    void push(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        } else {
            std::cout << "Stack is empty!" << std::endl;
        }
    }

    void display() const {
        Node* current = top;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

private:
    Node* top;
};

int main() {
    LinkedStack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.display();
    stack.pop();
    stack.display();
    return 0;
}