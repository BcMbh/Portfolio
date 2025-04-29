#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkQueue {
private:
    Node* front;
    Node* rear;

public:
    LinkQueue() : front(nullptr), rear(nullptr) {}

    ~LinkQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(int value) {
        Node* newNode = new Node{value, nullptr};
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty, cannot dequeue.\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
        if (front == nullptr) {
            rear = nullptr;
        }
    }

    int peek() const {
        if (isEmpty()) {
            std::cerr << "Queue is empty, cannot peek.\n";
            exit(EXIT_FAILURE);
        }
        return front->data;
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Queue is empty.\n";
            return;
        }
        Node* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};

int main() {
    LinkQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Queue contents: ";
    queue.display();

    std::cout << "Front element: " << queue.peek() << "\n";

    queue.dequeue();
    std::cout << "Queue contents after dequeue: ";
    queue.display();

    return 0;
}