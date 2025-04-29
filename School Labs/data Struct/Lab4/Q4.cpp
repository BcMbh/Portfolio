#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

int main() {
    node *head = nullptr;  // Initialize the head as NULL (empty list)
    node *temp;            // Temporary pointer for creating nodes
    int i, x;

    // Loop to create 6 nodes
    for (i = 0; i < 6; i++) {
        temp = new node;       // Create a new node
        cout << "Enter data for node " << i + 1 << ": ";
        cin >> x;              // Input data from the user
        temp->data = x;        // Assign data to the new node
        temp->next = head;     // Make the new node point to the previous head
        head = temp;           // Update head to point to the new node
    }

    // Display the linked list
    cout << "The linked list is: ";
    temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;

    return 0;
}
